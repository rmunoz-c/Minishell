/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:01:25 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/12 21:32:12 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/minishell.h"

void	insert_split_tokens(t_token_list *list, size_t index,
	char **parts, t_token *ref)
{
	size_t	j;
	t_token	new_token;

	free(ref->value);
	ref->value = ft_strdup(parts[0]);
	ref->length = ft_strlen(parts[0]);
	ref->in_single_quote = 0;
	ref->in_double_quote = 0;
	j = 1;
	while (parts[j])
	{
		new_token.type = TOKEN_WORD;
		new_token.value = ft_strdup(parts[j]);
		new_token.length = ft_strlen(parts[j]);
		new_token.in_single_quote = ref->in_single_quote;
		new_token.in_double_quote = ref->in_double_quote;
		token_list_insert(list, index + j, new_token);
		j++;
	}
}

void	split_expanded_token(t_token_list *list)
{
	size_t	i;
	char	**parts;

	i = 0;
	while (i < list->size)
	{
		if (list->array[i].type == TOKEN_WORD
			&& !list->array[i].in_single_quote
			&& !list->array[i].in_double_quote
			&& ft_strchr(list->array[i].value, ' '))
		{
			parts = ft_split(list->array[i].value, ' ');
			if (!parts)
				return ;
			insert_split_tokens(list, i, parts, &list->array[i]);
			ft_free_array(parts);
		}
		i++;
	}
}
