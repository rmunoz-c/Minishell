/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:08:27 by enogueir          #+#    #+#             */
/*   Updated: 2025/03/27 19:18:28 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token_list.h"
#include "../libft/libft.h"

static int	token_list_expand(t_token_list *list)
{
	t_token	*new_array;
	size_t	i;
	size_t	new_capacity;

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

void	token_list_init(t_token_list *list)
{
	list->size = 0;
	list->capacity = 8;
	list->array = malloc(sizeof(t_token) * list->capacity);
	if (!list->array)
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

int	token_list_add(t_token_list *list, t_token_type type, const char *val)
{
	size_t	len;
	char	*dup;

	if (!val || val[0] == '\0')
		return (1);
	if (list->size >= list->capacity)
		if (!token_list_expand(list))
			return (0);
	len = ft_strlen(val);
	dup = ft_substr(val, 0, len);
	if (!dup)
		return (0);
	list->array[list->size].type = type;
	list->array[list->size].value = dup;
	list->array[list->size].length = len;
	list->size++;
	return (1);
}
