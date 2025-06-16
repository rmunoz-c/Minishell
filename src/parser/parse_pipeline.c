/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:20:25 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/12 21:50:08 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

static size_t	find_last_pipe(t_token_list *list, size_t start, size_t end)
{
	size_t	i;

	i = end;
	while (i-- > start)
	{
		if (list->array[i].type == TOKEN_PIPE)
			return (i);
	}
	return ((size_t)-1);
}

t_ast_node	*parse_pipeline(t_token_list *list, size_t start, size_t end)
{
	size_t			pipe_index;
	t_ast_node		*left;
	t_ast_node		*right;
	t_ast_node		*pipe_node;

	pipe_index = find_last_pipe(list, start, end);
	if (pipe_index != (size_t)-1)
	{
		left = parse_pipeline(list, start, pipe_index);
		right = parse_command(list, pipe_index + 1, end);
		if (!left || !right)
			return (ast_node_free(left), ast_node_free(right), NULL);
		pipe_node = ast_node_create(NODE_PIPE, NULL);
		if (!pipe_node)
			return (ast_node_free(left), ast_node_free(right), NULL);
		pipe_node->left = left;
		pipe_node->right = right;
		return (pipe_node);
	}
	return (parse_command(list, start, end));
}
