/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:09:43 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/20 20:28:57 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	count_env(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static int	init_env_entry(t_envp *entry, const char *env)
{
	char	*equal;

	equal = ft_strchr(env, '=');
	if (!equal)
	{
		entry->key = ft_substr(env, 0, ft_strlen(env));
		entry->value = ft_strdup("");
	}
	else
	{
		entry->key = ft_substr(env, 0, (size_t)(equal - env));
		entry->value = ft_strdup(equal + 1);
	}
	if (!entry->key || !entry->value)
		return (0);
	return (1);
}

t_envp	*dup_envp_struct(char **envp, size_t *count)
{
	t_envp	*result;
	size_t	i;

	*count = count_env(envp);
	result = malloc(sizeof(t_envp) * (*count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < *count)
	{
		if (!init_env_entry(&result[i], envp[i]))
		{
			free_envp(result, i);
			return (NULL);
		}
		i++;
	}
	result[i].key = NULL;
	result[i].value = NULL;
	return (result);
}

int	remove_envp_entry(t_minishell *shell, const char *key)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < shell->env_count)
	{
		if (ft_strcmp(shell->envp[i].key, key) == 0)
		{
			free(shell->envp[i].key);
			free(shell->envp[i].value);
			j = i;
			while (j + 1 < shell->env_count)
			{
				shell->envp[j] = shell->envp[j + 1];
				j++;
			}
			shell->env_count--;
			shell->envp[shell->env_count].key = NULL;
			shell->envp[shell->env_count].value = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

void	free_envp(t_envp *envp, size_t count)
{
	size_t	i;

	if (!envp)
		return ;
	i = 0;
	while (i < count)
	{
		free(envp[i].key);
		free(envp[i].value);
		i++;
	}
	free(envp);
}
