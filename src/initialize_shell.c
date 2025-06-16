/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_shell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:25:31 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/16 22:30:29 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	init_shell_struct(t_minishell *shell)
{
	shell->envp = NULL;
	shell->env_count = 0;
	shell->exit_status = 0;
	shell->tokens = NULL;
	return (1);
}

static int	dup_env(t_minishell *shell, char **envp)
{
	shell->envp = dup_envp_struct(envp, &shell->env_count);
	if (!shell->envp)
		return (0);
	return (1);
}

t_minishell	*initialize_shell(char **envp)
{
	t_minishell	*shell;

	shell = malloc(sizeof(t_minishell));
	if (!shell)
		return (NULL);
	if (!init_shell_struct(shell))
	{
		free(shell);
		return (NULL);
	}
	if (!dup_env(shell, envp))
	{
		free(shell);
		return (NULL);
	}
	return (shell);
}
