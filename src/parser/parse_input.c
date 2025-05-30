/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:31:39 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/29 21:41:15 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/parser.h"
#include "../../includes/token_list.h"
#include "../../includes/tokenizer.h"
#include "../../libft/libft.h"

t_ast_node	*parse_input(t_token_list *list)
{
	if (!list || list->size == 0)
		return (NULL);
	if (list->array[0].type == TOKEN_PIPE
		|| list->array[list->size - 1].type == TOKEN_PIPE)
	{
		add_special_token(list, TOKEN_ERROR, "Pipe at start or end", 21);
		return (NULL);
	}
	return (parse_pipeline(list, 0, list->size));
}
