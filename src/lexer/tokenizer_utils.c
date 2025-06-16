/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:04:55 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/12 21:38:08 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"
#include "../includes/minishell.h"

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

int	add_token(t_token_list *list, t_token_type type, char *text, int len)
{
	t_token	token;

	token.type = type;
	token.value = ft_strdup(text);
	if (!token.value)
		return (0);
	token.length = len;
	token.in_single_quote = 0;
	token.in_double_quote = 0;
	token_list_add_token(list, &token);
	return (1);
}

int	add_token_quoted(t_token_list *list, t_token_data data)
{
	t_token	token;

	token.type = data.type;
	token.value = ft_strdup(data.text);
	if (!token.value)
		return (0);
	token.length = data.length;
	token.in_single_quote = (data.quote == '\'');
	token.in_double_quote = (data.quote == '\"');
	token_list_add_token(list, &token);
	return (1);
}

size_t	handle_special_char(const char *str, t_token_list *list, size_t i)
{
	if (str[i] == '>' && str[i + 1] == '>')
		return (add_token(list, TOKEN_REDIRECT_OUT_DBL, ">>", 2), 2);
	if (str[i] == '<' && str[i + 1] == '<')
		return (add_token(list, TOKEN_REDIRECT_IN_DBL, "<<", 2), 2);
	if (str[i] == '>')
		return (add_token(list, TOKEN_REDIRECT_OUT, ">", 1), 1);
	if (str[i] == '<')
		return (add_token(list, TOKEN_REDIRECT_IN, "<", 1), 1);
	if (str[i] == '|')
		return (add_token(list, TOKEN_PIPE, "|", 1), 1);
	return (1);
}
