/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:58:40 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/08 22:41:52 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/execute.h"
#include "../../includes/minishell.h"

static int	setup_redirections(t_ast_node *node)
{
	int		fd;
	size_t	i;
	size_t	last_heredoc_index;

	i = 0;
	last_heredoc_index = (size_t)-1;
	while (i < node->redir_count)
	{
		if (node->redirs[i].type == TOKEN_REDIRECT_IN_DBL)
			last_heredoc_index = i;
		i++;
	}
	i = 0;
	while (i < node->redir_count)
	{
		if (node->redirs[i].type == TOKEN_REDIRECT_IN_DBL)
		{
			fd = node->redirs[i].fd;
			if (fd >= 0)
			{
				if (i == last_heredoc_index)
				{
					if (dup2(fd, STDIN_FILENO) < 0)
						perror("dup2 heredoc final");
				}
				close(fd);
				node->redirs[i].fd = -1;
			}
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
			fd = open(node->redirs[i].filename, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
				return (perror(node->redirs[i].filename), close(fd), -1);
			close(fd);
		}
		else if (node->redirs[i].type == TOKEN_REDIRECT_OUT_DBL)
		{
			fd = open(node->redirs[i].filename, O_WRONLY | O_CREAT | O_APPEND,
					0644);
			if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
				return (perror(node->redirs[i].filename), close(fd), -1);
			close(fd);
		}
		i++;
	}
	return (0);
}

static pid_t	pipe_fork_left(t_ast_node *node, t_minishell *shell, int *fd)
{
	pid_t	pid;

	if (!node)
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			perror("dup2 left");
		close(fd[1]);
		if (node->type == NODE_COMMAND && setup_redirections(node) < 0)
			exit(EXIT_FAILURE);
		exit(execute_node(node, shell));
	}
	return (pid);
}

static pid_t	pipe_fork_right(t_ast_node *node, t_minishell *shell, int *fd)
{
	pid_t	pid;

	if (!node)
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
			perror("dup2 right");
		close(fd[0]);
		if (node->type == NODE_COMMAND && setup_redirections(node) < 0)
			exit(EXIT_FAILURE);
		exit(execute_node(node, shell));
	}
	return (pid);
}

int	execute_pipe_node(t_ast_node *node, t_minishell *shell)
{
	int		fd[2];
	pid_t	left;
	pid_t	right;
	int		status;

	if (pipe(fd) < 0)
		return (perror("pipe"), 1);
	left = pipe_fork_left(node->left, shell, fd);
	right = pipe_fork_right(node->right, shell, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(left, NULL, 0);
	waitpid(right, &status, 0);
	return (WEXITSTATUS(status));
}

int	execute_node(t_ast_node *node, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	if (!node)
		return (1);
	if (node->type == NODE_PIPE)
		return (execute_pipe_node(node, shell));
	if (node->type == NODE_COMMAND)
	{
		if (setup_redirections(node) < 0)
			exit(EXIT_FAILURE);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 1);
		if (pid == 0)
		{
			handle_external_command(node->args, shell->envp);
			exit(EXIT_FAILURE);
		}
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (1);
}
