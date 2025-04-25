/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:58:40 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/25 20:45:48 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ast.h"
#include "../../includes/execute.h"

static int setup_redirections(t_ast_node *node)
{
    int fd;
    size_t i = 0;
    size_t last_heredoc_index = (size_t)-1;

    // Primero encuentra cuál es el último heredoc
    i = 0;
    while (i < node->redir_count)
    {
        if (node->redirs[i].type == TOKEN_REDIRECT_IN_DBL)
            last_heredoc_index = i;
        i++;
    }

    // Ahora procesa las redirecciones
    i = 0;
    while (i < node->redir_count)
    {
        if (node->redirs[i].type == TOKEN_REDIRECT_IN_DBL)
        {
            fd = read_heredoc(node->redirs[i].filename);
            if (fd < 0)
                return (perror("heredoc"), -1);

            if (i == last_heredoc_index)
            {
                // SOLO si es el último heredoc hacemos dup2
                if (dup2(fd, STDIN_FILENO) < 0)
                {
                    perror("dup2 heredoc final");
                    close(fd);
                    return (-1);
                }
            }
            // En cualquier caso, SIEMPRE cerramos este descriptor, sea o no el último tras dup2
            close(fd);
        }
        else if (node->redirs[i].type == TOKEN_REDIRECT_IN)
        {
            fd = open(node->redirs[i].filename, O_RDONLY);
            if (fd < 0)
                return (perror(node->redirs[i].filename), -1);
            if (dup2(fd, STDIN_FILENO) < 0)
                return (perror("dup2 input"), close(fd), -1);
            close(fd);
        }
        else if (node->redirs[i].type == TOKEN_REDIRECT_OUT)
        {
            fd = open(node->redirs[i].filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
                return (perror(node->redirs[i].filename), close(fd), -1);
            close(fd);
        }
        else if (node->redirs[i].type == TOKEN_REDIRECT_OUT_DBL)
        {
            fd = open(node->redirs[i].filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
                return (perror(node->redirs[i].filename), close(fd), -1);
            close(fd);
        }
        i++;
    }
    return (0);
}


int	execute_node(t_ast_node *node, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	if (!node || node->type != NODE_COMMAND)
		return (1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		if (setup_redirections(node) < 0)
			exit(EXIT_FAILURE);
		execve(node->args[0], node->args, shell->envp);
		perror(node->args[0]);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
