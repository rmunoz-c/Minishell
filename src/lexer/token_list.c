/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:14:26 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/20 18:59:22 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token_list.h"
#include "../includes/minishell.h"

void	token_list_init(t_token_list *list)
{
	list->array = NULL;
	list->size = 0;
	list->capacity = 0;
}

void	token_list_free(t_token_list *list)
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

int	token_list_add_token(t_token_list *list, t_token *token)
{
	t_token	*new_array;
	size_t	i;

	if (list->size >= list->capacity)
	{
		list->capacity = (list->capacity + 1) * 2;
		new_array = malloc(sizeof(t_token) * list->capacity);
		if (!new_array)
			return (0);
		i = 0;
		while (i < list->size)
		{
			new_array[i] = list->array[i];
			i++;
		}
		free(list->array);
		list->array = new_array;
	}
	list->array[list->size] = *token;
	list->size++;
	return (1);
}

static int	insert_and_expand(t_token_list *list, size_t index, t_token token)
{
	t_token	*new_array;
	size_t	i;

	list->capacity = (list->capacity + 1) * 2;
	new_array = malloc(sizeof(t_token) * list->capacity);
	if (!new_array)
		return (0);
	i = 0;
	while (i < index)
	{
		new_array[i] = list->array[i];
		i++;
	}
	new_array[i] = token;
	while (i < list->size)
	{
		new_array[i + 1] = list->array[i];
		i++;
	}
	free(list->array);
	list->array = new_array;
	return (1);
}

void	token_list_insert(t_token_list *list, size_t index, t_token token)
{
	size_t	i;

	if (list->size >= list->capacity)
	{
		if (!insert_and_expand(list, index, token))
			return ;
	}
	else
	{
		i = list->size;
		while (i > index)
		{
			list->array[i] = list->array[i - 1];
			i--;
		}
		list->array[index] = token;
	}
	list->size++;
}
