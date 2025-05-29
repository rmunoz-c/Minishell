/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:33:21 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/29 21:40:54 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/parser.h"
#include "../../includes/token_list.h"
#include "../../includes/tokenizer.h"
#include "../../libft/libft.h"

static int	handle_redirect(t_token_list *list, size_t i, size_t end,
		t_ast_node *cmd)
{
	if ((i + 1) >= end || list->array[i + 1].type != TOKEN_WORD)
	{
		add_special_token(list, TOKEN_ERROR, "Syntax error near redirect", 27);
		return (0);
	}
	if (!add_redirection(cmd, list->array[i].type, list->array[i + 1].value))
	{
		add_special_token(list, TOKEN_ERROR, "Failed to add redirection", 26);
		return (0);
	}
	return (1);
}

static void	parse_redirections(t_token_list *list, size_t start, size_t end,
		t_ast_node *cmd)
{
	size_t	i;

	i = start;
	while (i < end)
	{
		if (list->array[i].type == TOKEN_REDIRECT_IN
			|| list->array[i].type == TOKEN_REDIRECT_OUT
			|| list->array[i].type == TOKEN_REDIRECT_IN_DBL
			|| list->array[i].type == TOKEN_REDIRECT_OUT_DBL)
		{
			if (!handle_redirect(list, i, end, cmd))
				return ;
			i += 2;
			continue ;
		}
		i++;
	}
}

t_ast_node	*parse_command(t_token_list *list, size_t start, size_t end)
{
	char		**args;
	t_ast_node	*cmd;

	// size_t i;
	if (start >= end)
		return (NULL);
	args = collect_args(list, start, end);
	if (!args)
		return (NULL);
	cmd = ast_node_create(NODE_COMMAND, args);
	// i = 0;
	// while (args[i])
	// {
	// 	free(args[i]);
	// 	i++;
	// }
	// free(args);
	if (!cmd)
		return (NULL);
	parse_redirections(list, start, end, cmd);
	return (cmd);
}
