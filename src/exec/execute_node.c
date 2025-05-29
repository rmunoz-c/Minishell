/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:58:40 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/28 19:37:11 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/execute.h"
#include "../../includes/builtins.h"
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
	int		save_stdin;
	int		save_stdout;

	if (!node)
		return (1);
	if (node->type == NODE_COMMAND && is_builtin(node->args[0]))
	{
		save_stdin = dup(STDIN_FILENO);
		save_stdout = dup(STDOUT_FILENO);
		if (setup_redirections(node) < 0)
		{
			shell->exit_status = errno;
			dup2(save_stdin, STDIN_FILENO);
			dup2(save_stdout, STDOUT_FILENO);
			close(save_stdin);
			close(save_stdout);
			return (shell->exit_status);
		}
		shell->exit_status = execute_builtin(node->args, shell);
		dup2(save_stdin, STDIN_FILENO);
		dup2(save_stdout, STDOUT_FILENO);
		close(save_stdin);
		close(save_stdout);
		return (shell->exit_status);
	}
	if (node->type == NODE_PIPE)
	{
		shell->exit_status = execute_pipe_node(node, shell);
		return (shell->exit_status);
	}
	if (node->type == NODE_COMMAND)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("minishell: fork");
			shell->exit_status = 1;
			return (shell->exit_status);
		}
		if (pid == 0)
		{
			if (setup_redirections(node) < 0)
				_exit(errno);
			handle_external_command(node->args, shell);
			_exit(errno);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
            shell->exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            shell->exit_status = 128 + WTERMSIG(status);
        return (shell->exit_status);
	}
	return (1);
}


