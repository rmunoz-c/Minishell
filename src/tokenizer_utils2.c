/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:30:17 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025/03/27 20:20:33 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"
#include "../libft/libft.h"

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

int	expand_and_join(const char *str, size_t *pos, char **result)
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

char	*build_inside_string(const char *substr)
{
	size_t	pos;
	char	*result;
	char	*temp;

	pos = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (substr[pos])
	{
		if (substr[pos] == '$' && substr[pos + 1])
			temp = expand_dollar(substr, &pos);
		else
		{
			temp = ft_substr(substr, pos, 1);
			pos++;
		}
		result = ft_strjoinfree(result, temp);
		free(temp);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*expand_inside_string(const char *substr)
{
	return (build_inside_string(substr));
}
