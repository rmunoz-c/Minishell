/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:07:35 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/10 18:55:55 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"
#include "../../includes/token_list.h"
#include "../../libft/libft.h"

size_t	handle_quote(const char *str, t_token_list *list, size_t start)
{
	char	quote;
	char	*quoted;
	size_t	len;

	quote = str[start];
	len = start + 1;
	while (str[len] && str[len] != quote)
		len++;
	if (!str[len])
		return (token_list_add(list, TOKEN_ERROR, "Unclosed quote"), 1);
	quoted = ft_substr(str, start + 1, len - start - 1);
	if (!quoted)
		return (len - start + 1);
	token_list_add(list, TOKEN_WORD, quoted);
	free(quoted);
	return (len - start + 1);
}

size_t	handle_special_char(const char *str, t_token_list *list, size_t i)
{
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (token_list_add(list, TOKEN_REDIRECT_OUT_DBL, ">>"), 2);
		else
			return (token_list_add(list, TOKEN_REDIRECT_OUT, ">"), 1);
	}
	else if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (token_list_add(list, TOKEN_REDIRECT_IN_DBL, "<<"), 2);
		else
			return (token_list_add(list, TOKEN_REDIRECT_IN, "<"), 1);
	}
	else if (str[i] == '|')
		return (token_list_add(list, TOKEN_PIPE, "|"), 1);
	return (1);
}

size_t	handle_word(const char *str, t_token_list *list, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] && !isspace(str[*i]) && !is_quote(str[*i])
		&& str[*i] != '|' && str[*i] != '<' && str[*i] != '>')
		(*i)++;
	if (*i > start)
		token_list_add(list, TOKEN_WORD, ft_substr(str, start, *i - start));
	return (0);
}

void	tokenize_input(const char *str, t_token_list *list)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (isspace(str[i]))
			i++;
		else if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
			i += handle_dollar_quote_token(str, list, i);
		else if (is_quote(str[i]))
			i += handle_quote(str, list, i);
		else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			i += handle_special_char(str, list, i);
		else
			handle_word(str, list, &i);
	}
}
