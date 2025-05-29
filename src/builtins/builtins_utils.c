/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:31:00 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/28 19:07:35 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../libft/libft.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	execute_builtin(char **args, t_minishell *shell)
{
	if (!args || !args[0])
		return (1);
	if (!ft_strcmp(args[0], "echo"))
		return (builtin_echo(args, shell));
	if (!ft_strcmp(args[0], "cd"))
		return (builtin_cd(args, shell));
	if (!ft_strcmp(args[0], "pwd"))
		return (builtin_pwd(shell));
	if (!ft_strcmp(args[0], "export"))
		return (builtin_export(args, shell));
	if (!ft_strcmp(args[0], "unset"))
		return (builtin_unset(args, shell));
	if (!ft_strcmp(args[0], "env"))
		return (builtin_env(shell));
	if (!ft_strcmp(args[0], "exit"))
		return (builtin_exit(args, shell));
	return (1);
}
