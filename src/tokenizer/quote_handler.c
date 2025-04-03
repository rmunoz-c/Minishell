/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:49:06 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/03 17:54:18 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"
#include "../../libft/libft.h"

static size_t	find_closing_quote(const char *str, size_t start, char quote)
{
	while (str[start])
	{
		if (str[start] == quote)
			return (start);
		start++;
	}
	return ((size_t)-1);
}

size_t	handle_quote_token(const char *str, t_token_list *list, size_t start)
{
	size_t	end;
	char	*quoted;

	end = find_closing_quote(str, start + 1, str[start]);
	if (end == (size_t)-1)
	{
		token_list_add(list, TOKEN_ERROR, "Unclosed quote");
		return (1);
	}
	quoted = ft_substr(str, start + 1, end - start - 1);
	if (!quoted)
		return (end - start + 1);
	token_list_add(list, TOKEN_WORD, quoted);
	free(quoted);
	return (end - start + 1);
}
