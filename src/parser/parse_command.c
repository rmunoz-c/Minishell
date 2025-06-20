/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:23:11 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/20 20:30:13 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

static size_t	count_args(t_token_list *list, size_t start, size_t end)
{
	size_t	count;

	count = 0;
	while (start < end)
	{
		if (list->array[start].type == TOKEN_WORD)
			count++;
		else if (list->array[start].type == TOKEN_REDIRECT_IN
			|| list->array[start].type == TOKEN_REDIRECT_OUT
			|| list->array[start].type == TOKEN_REDIRECT_IN_DBL
			|| list->array[start].type == TOKEN_REDIRECT_OUT_DBL)
			start++;
		start++;
	}
	return (count);
}

static int	fill_args_and_redirs(t_ast_node *cmd, t_token_list *list,
									size_t start, size_t end)
{
	size_t	arg_i;
	t_token	*tok;

	arg_i = 0;
	while (start < end)
	{
		tok = &list->array[start];
		if (tok->type == TOKEN_WORD)
			cmd->args[arg_i++] = ft_strdup(tok->value);
		else if (tok->type == TOKEN_REDIRECT_IN
			|| tok->type == TOKEN_REDIRECT_OUT
			|| tok->type == TOKEN_REDIRECT_IN_DBL
			|| tok->type == TOKEN_REDIRECT_OUT_DBL)
		{
			if (start + 1 >= end || list->array[start + 1].type != TOKEN_WORD)
				return (printf("minishell: syntax error in redirection\n"), 0);
			if (!add_redirection(cmd, tok->type, list->array[start + 1].value,
					list->array[start + 1].in_double_quote
					|| list->array[start + 1].in_single_quote))
				return (0);
			start++;
		}
		start++;
	}
	return (cmd->args[arg_i] = NULL, 1);
}

t_ast_node	*parse_command(t_token_list *list, size_t start, size_t end)
{
	t_ast_node	*cmd;
	size_t		arg_count;
	char		**args;

	arg_count = count_args(list, start, end);
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	cmd = ast_node_create(NODE_COMMAND, args);
	if (!cmd || !cmd->args)
		return (ast_node_free(cmd), NULL);
	if (!fill_args_and_redirs(cmd, list, start, end))
		return (ast_node_free(cmd), NULL);
	return (cmd);
}
