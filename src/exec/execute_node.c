/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:22:09 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/16 18:34:17 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/minishell.h"
#include "../../includes/execute.h"

static void	handle_exec_status(int status, t_minishell *shell)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	else
		shell->exit_status = 1;
}

static void	fork_and_exec(t_ast_node *node, t_minishell *shell)
{
	char	**flat_env;
	char	*cmd_path;

	if (setup_redirections(node) < 0)
		exit(1);
	flat_env = flatten_envp(shell->envp, shell->env_count);
	cmd_path = resolve_cmd_path(node, flat_env);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_flat_env(flat_env);
		exit(127);
	}
	execve(cmd_path, node->args, flat_env);
	perror("execve");
	free(cmd_path);
	free_flat_env(flat_env);
	exit(127);
}

static int	exec_external_command(t_ast_node *node, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
		fork_and_exec(node, shell);
	waitpid(pid, &status, 0);
	handle_exec_status(status, shell);
	return (shell->exit_status);
}

static int	exec_builtin_with_redir(t_ast_node *node, t_minishell *shell)
{
	int	save_in;
	int	save_out;
	int	result;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (setup_redirections(node) < 0)
	{
		dup2(save_in, STDIN_FILENO);
		dup2(save_out, STDOUT_FILENO);
		close(save_in);
		close(save_out);
		shell->exit_status = errno;
		return (shell->exit_status);
	}
	result = execute_builtin(node, shell);
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(save_in);
	close(save_out);
	shell->exit_status = result;
	return (result);
}

int	execute_node(t_ast_node *node, t_minishell *shell)
{
	if (!node)
		return (0);
	if (node->type == NODE_PIPE)
		return (execute_pipe_node(node, shell));
	if (node->type == NODE_COMMAND && node->args)
	{
		if (is_builtin(node->args[0]))
			return (exec_builtin_with_redir(node, shell));
		return (exec_external_command(node, shell));
	}
	return (0);
}
