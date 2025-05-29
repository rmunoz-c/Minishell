/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:52:30 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/28 19:16:01 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token_list.h"
#include "../libft/libft.h"

void	free_tokens(t_token_list *list)
{
	size_t	i;

	i = 0;
	while (i < list->size)
	{
		free(list->array[i].value);
		i++;
	}
	free(list->array);
	list->array = NULL;
	list->size = 0;
	list->capacity = 0;
}

void	free_envp(t_envp *envp, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(envp[i].key);
		free(envp[i].value);
		i++;
	}
	free(envp);
}

void	free_all(t_minishell *data)
{
	free_tokens(data->tokens);
	free_envp(data->envp, data->env_count);
}

void	free_flat_env(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
