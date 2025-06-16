/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_assign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:54:47 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/12 21:46:38 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

static int	add_assignment_token(const char *str, t_assign_parts pos,
		t_token_list *list, char quote)
{
	char			*prefix;
	char			*value;
	char			*full;
	t_token_data	data;

	prefix = ft_substr(str, pos.var_start, pos.equal_pos - pos.var_start + 1);
	if (!prefix)
		return (0);
	value = ft_substr(str, pos.equal_pos + 2, pos.end - (pos.equal_pos + 2));
	if (!value)
		return (free(prefix), 0);
	full = ft_strjoin(prefix, value);
	free(prefix);
	free(value);
	if (!full)
		return (0);
	data.type = TOKEN_WORD;
	data.text = full;
	data.length = ft_strlen(full);
	data.quote = quote;
	add_token_quoted(list, data);
	free(full);
	return (1);
}

static int	find_quote_end_index(const char *str, size_t i, char quote)
{
	size_t	j;

	j = i + 2;
	while (str[j] && str[j] != quote)
		j++;
	if (!str[j])
		return (-1);
	return (j);
}

static int	assignment_pattern_get_end(const char *str, size_t *i,
	char *quote, t_assign_parts *pos)
{
	int	end;

	*quote = str[*i + 1];
	end = find_quote_end_index(str, *i, *quote);
	if (end == -1)
		return (0);
	pos->end = (size_t)end;
	*i = end + 1;
	return (1);
}

static int	validate_assignment_pattern(const char *str, t_assign_parts *pos,
	size_t *i, t_token_list *list)
{
	char	quote;

	if (!assignment_pattern_get_end(str, i, &quote, pos))
		return (0);
	if (!add_assignment_token(str, *pos, list, quote))
		return (-1);
	return (1);
}

int	try_merge_assignment_with_quote(const char *str, t_token_list *list,
	size_t *i)
{
	t_assign_parts	pos;
	int				result;

	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (0);
	pos.var_start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	pos.equal_pos = *i;
	if (str[*i] == '=' && is_quote(str[*i + 1]))
	{
		result = validate_assignment_pattern(str, &pos, i, list);
		if (result != 0)
			return (result > 0);
	}
	*i = pos.var_start;
	return (0);
}
