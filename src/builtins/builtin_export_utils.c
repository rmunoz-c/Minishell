/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:59:13 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/12 21:18:25 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_update_existing(const char *arg, char *equal, size_t len,
		t_minishell *sh)
{
	size_t	i;

	i = 0;
	while (i < sh->env_count)
	{
		if (!ft_strncmp(sh->envp[i].key, arg, len)
			&& sh->envp[i].key[len] == '\0')
		{
			if (equal)
			{
				free(sh->envp[i].value);
				sh->envp[i].value = ft_strdup(equal + 1);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

void	export_add_new(const char *arg, char *equal, size_t len,
		t_minishell *sh)
{
	sh->envp[sh->env_count].key = ft_substr(arg, 0, len);
	if (equal)
		sh->envp[sh->env_count].value = ft_strdup(equal + 1);
	else
		sh->envp[sh->env_count].value = ft_strdup("");
	sh->env_count++;
}

void	export_one(const char *arg, t_minishell *sh)
{
	char	*equal;
	size_t	len;

	equal = ft_strchr(arg, '=');
	if (equal)
		len = (size_t)(equal - arg);
	else
		len = ft_strlen(arg);
	if (!export_update_existing(arg, equal, len, sh))
		export_add_new(arg, equal, len, sh);
}
