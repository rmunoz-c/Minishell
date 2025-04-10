/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:50:24 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/10 16:36:44 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/token_list.h"
#include "../../libft/libft.h"
#include <stdlib.h>

char	*get_env_value(const char *name)
{
	char	*value;

	value = getenv(name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char *expand_dollar(const char *str, size_t *i)
{
	size_t start;
	char  *var;
	char  *val;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_exit_status));
	}
	if (str[*i] == '\'' || str[*i] == '"')
		return (ft_strdup("$"));
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (ft_strdup("$"));
	var = ft_substr(str, start, *i - start);
	val = get_env_value(var);
	free(var);
	return (val);
}


char	*expand_string(const char *str)
{
	size_t	i;
	char	*res;
	char	*tmp;
	char	*exp;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			exp = expand_dollar(str, &i);
			tmp = ft_strjoin(res, exp);
			(free(res), free(exp));
			res = tmp;
		}
		else
		{
			tmp = ft_substr(str, (i++, i - 1), 1);
			exp = ft_strjoin(res, tmp);
			(free(res), free(tmp));
			(res = exp);
		}
	}
	return (res);
}

void	expand_token_list(t_token_list *list)
{
	size_t	i;
	char	*new;

	i = 0;
	while (i < list->size)
	{
		if (list->array[i].type == TOKEN_WORD)
		{
			new = expand_string(list->array[i].value);
			free(list->array[i].value);
			list->array[i].value = new;
		}
		i++;
	}
}

char	*expand_inside_string(const char *substr)
{
	return (expand_string(substr));
}
