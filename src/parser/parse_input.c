/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:18:12 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/12 21:13:48 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

static int	has_token_error(t_token_list *list)
{
	size_t	i;

	i = 0;
	while (i < list->size)
	{
		if (list->array[i].type == TOKEN_ERROR)
			return (1);
		i++;
	}
	return (0);
}

t_ast_node	*parse_input(t_token_list *list)
{
	if (!list || list->size == 0)
		return (NULL);
	if (has_token_error(list))
		return (NULL);
	if (!validate_token_syntax(list))
		return (NULL);
	return (parse_pipeline(list, 0, list->size));
}
