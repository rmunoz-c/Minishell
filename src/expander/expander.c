/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:41:02 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/05 19:03:45 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token_list.h"
#include "../includes/expander.h"

static void	expand_token(t_token_list *list, size_t i, t_minishell *shell)
{
	char	*expanded;
	t_token	*tok;

	tok = &list->array[i];
	if (tok->in_single_quote)
		return ;
	expanded = expand_string(tok->value, shell);
	if (!expanded)
		return ;
	free(tok->value);
	tok->value = expanded;
	tok->length = ft_strlen(expanded);
}

void	expand_token_list(t_token_list *list, t_minishell *shell)
{
	size_t	i;

	i = 0;
	while (i < list->size)
	{
		if (list->array[i].type == TOKEN_WORD)
			expand_token(list, i, shell);
		i++;
	}
	split_expanded_token(list);
}
