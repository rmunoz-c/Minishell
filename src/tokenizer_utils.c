/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:32:13 by enogueir          #+#    #+#             */
/*   Updated: 2025/03/27 20:08:33 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/tokenizer.h"
#include "../libft/libft.h"

int	is_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

char	*expand_dollar(const char *str, size_t *pos)
{
	char	*expanded;
	size_t	start;
	size_t	var_len;

	(*pos)++;
	if (str[*pos] == '?')
	{
		(*pos)++;
		expanded = expand_exit_status();
		return (expanded);
	}
	start = *pos;
	while (str[*pos] && (ft_isalnum(str[*pos]) || str[*pos] == '_'))
		(*pos)++;
	var_len = *pos - start;
	if (var_len == 0)
		return (ft_strdup(""));
	expanded = expand_variable(ft_substr(str, start, var_len));
	return (expanded);
}
