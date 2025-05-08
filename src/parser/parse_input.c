/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:31:39 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/05 14:34:05 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/parser.h"
#include "../../includes/token_list.h"
#include "../../libft/libft.h"

t_ast_node	*parse_input(t_token_list *list)
{
	if (!list || list->size == 0)
		return (NULL);
	if (list->array[0].type == TOKEN_PIPE || list->array[list->size
			- 1].type == TOKEN_PIPE)
	{
		token_list_add(list, TOKEN_ERROR, "Pipe at start or end");
		return (NULL);
	}
	return (parse_pipeline(list, 0, list->size));
}
