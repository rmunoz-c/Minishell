/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_envmod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:35:02 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/28 18:11:31 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../libft/libft.h"

t_envp	*envp_struct_realloc_with(t_envp *env, size_t *env_count,
		const char *key, const char *value)
{
	size_t	i;
	t_envp	*new_env;

	i = 0;
	while (i < *env_count)
		i++;
	new_env = malloc(sizeof(t_envp) * (i + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < *env_count)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i].key = ft_strdup(key);
	new_env[i].value = ft_strdup(value);
	i++;
	new_env[i].key = NULL;
	new_env[i].value = NULL;
	free(env);
	*env_count = i;
	return (new_env);
}

t_envp	*envp_struct_remove(t_envp *env, size_t *count, const char *key)
{
	size_t	i;
	size_t	j;
	t_envp	*new_env;

	new_env = malloc(sizeof(t_envp) * (*count + 1));
	if (!new_env)
		return (env);
	i = 0;
	j = 0;
	while (i < *count)
	{
		if (ft_strcmp(env[i].key, (char *)key) != 0)
			new_env[j++] = env[i];
		else
		{
			free(env[i].key);
			free(env[i].value);
		}
		i++;
	}
	new_env[j].key = NULL;
	new_env[j].value = NULL;
	*count = j;
	free(env);
	return (new_env);
}

static int	is_valid_identifier(const char *key)
{
	size_t	j;

	j = 0;
	if (!(ft_isalpha(key[j]) || key[j] == '_'))
		return (0);
	j++;
	while (key[j] && key[j] != '=')
	{
		if (!(ft_isalnum(key[j]) || key[j] == '_'))
			return (0);
		j++;
	}
	return (1);
}

int	builtin_export(char **args, t_minishell *shell)
{
	size_t	i;
	char	*eq;
	char	*key;
	char	*value;

	if (!args[1])
	{
		i = 0;
		while (i < shell->env_count)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(shell->envp[i].key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(shell->envp[i].value, 1);
			i++;
		}
		shell->exit_status = 0;
		return (0);
	}
	i = 1;
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (eq)
		{
			key = ft_substr(args[i], 0, (size_t)(eq - args[i]));
			value = ft_strdup(eq + 1);
		}
		else
		{
			key = ft_strdup(args[i]);
			value = ft_strdup("");
		}
		if (!is_valid_identifier(key))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			free(key);
			free(value);
			shell->exit_status = 1;
			return (1);
		}
		shell->envp = envp_struct_realloc_with(shell->envp, &shell->env_count,
				key, value);
		free(key);
		free(value);
		if (!shell->envp)
		{
			shell->exit_status = 1;
			return (1);
		}
		i++;
	}
	shell->exit_status = 0;
	return (0);
}

int	builtin_unset(char **args, t_minishell *shell)
{
	size_t	i;

	i = 1;
	while (args[i])
	{
		shell->envp = envp_struct_remove(shell->envp, &shell->env_count,
				args[i]);
		i++;
	}
    shell->exit_status = 0;
	return (0);
}
