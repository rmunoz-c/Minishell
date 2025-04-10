/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:34:21 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/10 17:43:37 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/token_list.h"
#include "../../includes/ast.h"
#include "../../libft/libft.h"


t_ast_node	*parse_pipeline(t_token_list *list, size_t start, size_t end)
{
	size_t	i;

	i = start;
	while (i < end)
	{
		if (list->array[i].type == TOKEN_PIPE)
		{
			t_ast_node *pipe_node = ast_node_create(NODE_PIPE, NULL);
			if (!pipe_node)
				return (NULL);
			pipe_node->left = parse_pipeline(list, start, i);
			pipe_node->right = parse_pipeline(list, i + 1, end);
			return (pipe_node);
		}
		i++;
	}
	return (parse_command(list, start, end));
}
