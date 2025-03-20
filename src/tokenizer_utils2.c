/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-19 18:30:17 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-03-19 18:30:17 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	append_char_to_result(char c, char **result)
{
	char	buff[2];
	char	*temp;

	buff[0] = c;
	buff[1] = '\0';
	temp = ft_strjoin(*result, buff);
	if (!temp)
		return (0);
	free(*result);
	*result = temp;
	return (1);
}

static int	expand_and_join(const char *str, size_t *pos, char **result)
{
	char	*temp;
	char	*expanded;

	expanded = expand_dollar(str, pos);
	if (!expanded)
		return (1);
	temp = ft_strjoin(*result, expanded);
	free(expanded);
	if (!temp)
		return (0);
	free(*result);
	*result = temp;
	return (1);
}


char	*build_expanded_word(const char *str, size_t *pos)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[*pos] && !isspace(str[*pos]) && !is_special_char(str[*pos]))
	{
		if (str[*pos] == '$' && str[*pos + 1])
		{
			if (!expand_and_join(str, pos, &result))
				return (free(result), NULL);
		}
		else
		{
			if (!append_char_to_result(str[*pos], &result))
				return (free(result), NULL);
			(*pos)++;
		}
	}
	return (result);
}