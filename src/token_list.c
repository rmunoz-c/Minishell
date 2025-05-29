/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:08:27 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/29 21:29:44 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token_list.h"
#include "../libft/libft.h"

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

static int	token_list_resize(t_token_list *list)
{
	t_token	*new_array;
	size_t	i;
	size_t	new_capacity;

	if (list->capacity == 0)
		new_capacity = 8;
	else
		new_capacity = list->capacity * 2;
	new_array = malloc(sizeof(t_token) * new_capacity);
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
	list->capacity = new_capacity;
	return (1);
}

int	token_list_add_token(t_token_list *list, t_token *token)
{
	if (list->size >= list->capacity)
	{
		if (!token_list_resize(list))
			return (0);
	}
	list->array[list->size].type = token->type;
	list->array[list->size].value = ft_strdup(token->value);
	if (!list->array[list->size].value)
		return (0);
	list->array[list->size].length = token->length;
	list->array[list->size].in_single_quote = token->in_single_quote;
	list->size++;
	return (1);
}
