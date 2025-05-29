/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:49:06 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/29 21:53:23 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"
#include "../../libft/libft.h"

// static size_t	find_closing_quote(const char *str, size_t start, char quote)
// {
// 	while (str[start])
// 	{
// 		if (str[start] == quote)
// 			return (start);
// 		start++;
// 	}
// 	return ((size_t)-1);
// }

// size_t	handle_quote_token(const char *str, t_token_list *list, size_t start)
// {
// 	size_t	end;
// 	char	*quoted;
// 	char	quote;
// 	size_t	length;

// 	quote = str[start];
// 	end = find_closing_quote(str, start + 1, quote);
// 	if (end == (size_t)-1)
// 	{
// 		add_special_token(list, TOKEN_ERROR, "Unclosed quote", 15);
// 		return (1);
// 	}
// 	quoted = ft_substr(str, start + 1, end - start - 1);
// 	if (!quoted)
// 		return (end - start + 1);
// 	length = end - start - 1;
// 	add_special_token(list, TOKEN_WORD, quoted, length);
// 	free(quoted);
// 	return (end - start + 1);
// }

int	add_special_token(t_token_list *list, t_token_type type, char *text,
		int len)
{
	t_token	token;

	token.type = type;
	token.value = ft_strdup(text);
	if (!token.value)
		return (0);
	token.length = len;
	token.in_single_quote = 0;
	token_list_add_token(list, &token);
	return (1);
}

int	add_special_token_quoted(t_token_list *list, t_token_type type,
	char *text, int len)
{
	t_token	token;

	token.type = type;
	token.value = ft_strdup(text);
	if (!token.value)
		return (0);
	token.length = len;
	token.in_single_quote = 1;
	token_list_add_token(list, &token);
	return (1);
}
