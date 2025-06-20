/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:55:06 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/17 22:05:05 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/builtins.h"
#include "../../includes/minishell.h"
#include "../../includes/execute.h"

int	execute_builtin(t_ast_node *node, t_minishell *shell)
{
	char	*cmd;

	cmd = node->args[0];
	if (!strcmp(cmd, "echo"))
		return (builtin_echo(node->args));
	if (!strcmp(cmd, "pwd"))
		return (builtin_pwd());
	if (!strcmp(cmd, "env"))
		return (builtin_env(shell->envp, shell->env_count));
	if (!strcmp(cmd, "exit"))
		return (builtin_exit(node, shell));
	if (!strcmp(cmd, "cd"))
		return (builtin_cd(node->args, shell));
	if (!strcmp(cmd, "export"))
		return (builtin_export(node->args, shell));
	if (!strcmp(cmd, "unset"))
		return (builtin_unset(node->args, shell));
	return (1);
}

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (!strcmp(cmd, "echo"))
		return (1);
	if (!strcmp(cmd, "cd"))
		return (1);
	if (!strcmp(cmd, "pwd"))
		return (1);
	if (!strcmp(cmd, "export"))
		return (1);
	if (!strcmp(cmd, "unset"))
		return (1);
	if (!strcmp(cmd, "env"))
		return (1);
	if (!strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	is_exit_command(t_ast_node *ast)
{
	if (!ast || ast->type != NODE_COMMAND || !ast->args || !ast->args[0])
		return (0);
	return (ft_strncmp(ast->args[0], "exit", 5) == 0);
}
