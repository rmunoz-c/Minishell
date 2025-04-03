/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:29:18 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/03 18:26:35 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"
#include "../../libft/libft.h"

int	handle_dollar_quote(const char *str, size_t *pos, char **res)
{
	char	*temp;
	size_t	start;
	char	quote;

	quote = str[*pos];
	(*pos)++;
	start = *pos;
	while (str[*pos] && str[*pos] != quote)
		(*pos)++;
	temp = ft_substr(str, start, *pos - start);
	if (!temp)
		return (0);
	*res = ft_strjoinfree(*res, temp);
	free(temp);
	if (!(*res))
		return (0);
	if (str[*pos] == quote)
		(*pos)++;
	return (1);
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
