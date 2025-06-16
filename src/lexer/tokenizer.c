/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:02:48 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/12 21:36:41 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

static size_t	tokenize_word(const char *str, t_token_list *list, size_t i)
{
	size_t	start;
	char	*word;

	start = i;
	while (str[i] && !is_special_char(str[i]) && !is_quote(str[i])
		&& !isspace(str[i]))
		i++;
	word = ft_substr(str, start, i - start);
	if (!word)
		return (i - start);
	add_token(list, TOKEN_WORD, word, i - start);
	free(word);
	return (i - start);
}

size_t	handle_quote(const char *str, t_token_list *list, size_t start)
{
	char			quote;
	char			*quoted;
	size_t			len;
	t_token_data	data;

	quote = str[start];
	len = start + 1;
	while (str[len] && str[len] != quote)
		len++;
	if (!str[len])
	{
		add_token(list, TOKEN_ERROR, "Unclosed quote", 15);
		return (1);
	}
	quoted = ft_substr(str, start + 1, len - start - 1);
	if (!quoted)
		return (len - start + 1);
	data.type = TOKEN_WORD;
	data.text = quoted;
	data.length = len - start - 1;
	data.quote = quote;
	add_token_quoted(list, data);
	free(quoted);
	return (len - start + 1);
}

void	tokenize_input(const char *str, t_token_list *list)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (isspace(str[i]))
			i++;
		else if (try_merge_assignment_with_quote(str, list, &i))
			continue ;
		else if (str[i] == '$' && is_quote(str[i + 1]))
		{
			i++;
			i += handle_quote(str, list, i);
		}
		else if (is_quote(str[i]))
			i += handle_quote(str, list, i);
		else if (is_special_char(str[i]))
			i += handle_special_char(str, list, i);
		else
			i += tokenize_word(str, list, i);
	}
}
