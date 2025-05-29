/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:32:13 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/29 20:57:15 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"
#include "../../libft/libft.h"

int	is_special_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

size_t	handle_dollar_quote_token(const char *str, t_token_list *list,
		size_t index)
{
	char	quote;
	size_t	start;
	size_t	end;
	char	*inner;
	size_t	length;

	quote = str[index + 1];
	index += 2;
	start = index;
	while (str[index] && str[index] != quote)
		index++;
	if (!str[index])
	{
		add_special_token(list, TOKEN_ERROR, "Unclosed quote after $", 23);
		return (index - (start - 2));
	}
	end = index;
	index++;
	inner = ft_substr(str, start, end - start);
	if (!inner)
		return (index - (start - 2));
	length = end - start;
	add_special_token(list, TOKEN_WORD, inner, length);
	free(inner);
	return (index - (start - 2));
}
