/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:52:30 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/07 19:15:19 by enogueir         ###   ########.fr       */
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

void	free_envp(char **envp)
{
	size_t	i;

	i = 0;
	while (envp && envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_all(t_minishell *data)
{
	free_tokens(data->tokens);
	free_envp(data->envp);
}
