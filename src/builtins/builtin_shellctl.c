/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_shellctl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:35:22 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/28 19:07:23 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/expander.h"
#include "../../libft/libft.h"

void	update_env(t_minishell *shell, const char *key, const char *value)
{
	size_t	i;
	char	*new_val;

	new_val = ft_strdup(value);
	if (!new_val)
		return ;
	i = 0;
	while (i < shell->env_count)
	{
		if (ft_strcmp(shell->envp[i].key, (char *)key) == 0)
		{
			free(shell->envp[i].value);
			shell->envp[i].value = new_val;
			return ;
		}
		i++;
	}
	shell->envp = envp_struct_realloc_with(shell->envp, &shell->env_count,
			(char *)key, new_val);
}

int	builtin_cd(char **args, t_minishell *shell)
{
	char	*oldpwd;
	char	*target;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("minishell: getcwd"), 1);
	if (!args[1] || args[1][0] == '\0')
		target = get_env_value("HOME", shell->envp, shell->env_count);
	else
		target = args[1];
	if (!target)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		free(oldpwd);
		shell->exit_status = 1;
		return (1);
	}
	if (chdir(target) < 0)
	{
		perror("minishell: cd");
		free(oldpwd);
		shell->exit_status = 1;
		return (1);
	}
	update_env(shell, "OLDPWD", oldpwd);
	free(oldpwd);
	newpwd = getcwd(NULL, 0);
	update_env(shell, "PWD", newpwd);
	free(newpwd);
	shell->exit_status = 0;
	return (0);
}

int	builtin_exit(char **args, t_minishell *shell)
{
	long status;
	size_t i;

	(void)shell;
	ft_putendl_fd("exit", 1);
	if (args[1])
	{
		i = 0;
		while (args[1][i])
		{
			if (!isdigit((unsigned char)args[1][i]))
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(args[1], 2);
				ft_putendl_fd(": numeric argument required", 2);
				exit(2);
			}
			i++;
		}
		status = ft_atoi(args[1]);
		exit((int)status);
	}
	exit(EXIT_SUCCESS);
}
