/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:59:38 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/16 23:20:05 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/minishell.h"
#include "../../includes/execute.h"

pid_t	fork_left_pipe(t_ast_node *node, int fd[2], t_minishell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute_node(node, shell);
		exit(shell->exit_status);
	}
	return (pid);
}

pid_t	fork_right_pipe(t_ast_node *node, int fd[2], t_minishell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute_node(node, shell);
		exit(shell->exit_status);
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
	left = fork_left_pipe(node->left, fd, shell);
	right = fork_right_pipe(node->right, fd, shell);
	close(fd[0]);
	close(fd[1]);
	waitpid(left, NULL, 0);
	waitpid(right, &status, 0);
	handle_exec_status(status, shell);
	return (0);
}
