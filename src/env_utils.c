/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:06:23 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/27 20:24:21 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token_list.h"
#include "../libft/libft.h"

t_envp	*dup_envp_struct(char **envp, size_t *out_count)
{
	size_t	count;
	size_t	i;
	t_envp	*new_env;
	char	*eq;

	count = 0;
	while (envp[count])
		count++;
	new_env = malloc(sizeof(t_envp) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		eq = ft_strchr(envp[i], '=');
		if (eq)
			new_env[i].key = ft_substr(envp[i], 0, (size_t)(eq - envp[i]));
		else
			new_env[i].key = ft_substr(envp[i], 0, ft_strlen(envp[i]));
		if (eq)
			new_env[i].value = ft_strdup(eq + 1);
		else
			new_env[i].value = ft_strdup("");
		i++;
	}
	new_env[count].key = NULL;
	new_env[count].value = NULL;
	*out_count = count;
	return (new_env);
}
