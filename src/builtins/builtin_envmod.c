/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_envmod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:40:01 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/12 21:19:59 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_value(t_envp *envp, size_t count, const char *key)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (!ft_strcmp(envp[i].key, key))
			return (envp[i].value);
		i++;
	}
	return (NULL);
}

static void	update_env_var(t_envp *envp, size_t count,
		const char *key, const char *new_value)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (!ft_strcmp(envp[i].key, key))
		{
			free(envp[i].value);
			envp[i].value = ft_strdup(new_value);
			return ;
		}
		i++;
	}
}

static void	print_cd_error(const char *arg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	else
		ft_putstr_fd("HOME", 2);
	perror(": ");
}

int	builtin_cd(char **argv, t_minishell *shell)
{
	const char	*target;
	char		*oldpwd;
	char		cwd[4096];

	oldpwd = getcwd(NULL, 0);
	if (!argv[1])
		target = get_env_value(shell->envp, shell->env_count, "HOME");
	else
		target = argv[1];
	if (!target || chdir(target) != 0)
	{
		print_cd_error(argv[1]);
		free(oldpwd);
		return (1);
	}
	if (oldpwd)
		update_env_var(shell->envp, shell->env_count, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		update_env_var(shell->envp, shell->env_count, "PWD", cwd);
	free(oldpwd);
	return (0);
}
