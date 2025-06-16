/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:13:22 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/12 21:53:03 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

static int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN
		|| type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_REDIRECT_IN_DBL
		|| type == TOKEN_REDIRECT_OUT_DBL);
}

int	validate_token_syntax(t_token_list *list)
{
	size_t		i;
	t_token		*tok;

	if (!list || !list->array || list->size == 0)
		return (1);
	i = 0;
	while (i < list->size)
	{
		tok = &list->array[i];
		if (tok->type == TOKEN_PIPE
			&& (i == 0 || i + 1 == list->size
				|| list->array[i + 1].type == TOKEN_PIPE))
			return (printf("minishell: syntax error, unexpected token `|'\n"),
				0);
		if (is_redirection(tok->type)
			&& (i + 1 == list->size || list->array[i + 1].type != TOKEN_WORD))
			return (printf("minishell: syntax error, unexpected `newline'\n"),
				0);
		i++;
	}
	return (1);
}
