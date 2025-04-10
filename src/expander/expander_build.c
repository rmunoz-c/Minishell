/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:29:18 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/10 16:52:40 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"
#include "../../libft/libft.h"

size_t handle_dollar_quote(const char *str, t_token_list *list, size_t i)
{
	char  quote;
	size_t start;
	size_t end;
	char  *inner;

	quote = str[i + 1];
	i += 2;
	start = i;
	while (str[i] && str[i] != quote)
		i++;
	if (!str[i])
	{
		token_list_add(list, TOKEN_ERROR, "Unclosed quote after $");
		return (i - (start - 2));
	}
	end = i;
	i++;
	inner = ft_substr(str, start, end - start);
	if (!inner)
		return (end - (start - 2));
	token_list_add(list, TOKEN_WORD, inner);
	free(inner);
	return (i - (start - 2));
}


char	*build_expanded_word(const char *str, size_t *pos)
{
	char	*res;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (str[*pos] && !isspace(str[*pos]) && !is_special_char(str[*pos]))
	{
		if (!process_expansion(str, pos, &res))
		{
			free(res);
			return (NULL);
		}
	}
	return (res);
}
