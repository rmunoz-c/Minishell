/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:07:35 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/03 18:46:11 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"
#include "../../includes/token_list.h"
#include "../../libft/libft.h"

size_t	handle_quote(const char *str, t_token_list *list, size_t start)
{
	char	quote;
	char	*quoted;
	size_t	len;

	quote = str[start];
	len = start + 1;
	while (str[len] && str[len] != quote)
		len++;
	if (!str[len])
		return (token_list_add(list, TOKEN_ERROR, "Unclosed quote"), 1);
	quoted = ft_substr(str, start + 1, len - start - 1);
	if (!quoted)
		return (len - start + 1);
	token_list_add(list, TOKEN_WORD, quoted);
	free(quoted);
	return (len - start + 1);
}

size_t	handle_special_char(char c, t_token_list *list)
{
	if (c == '|')
		token_list_add(list, TOKEN_PIPE, "|");
	else if (c == '>')
		token_list_add(list, TOKEN_REDIRECT_OUT, ">");
	else if (c == '<')
		token_list_add(list, TOKEN_REDIRECT_IN, "<");
	return (1);
}

size_t	handle_word(const char *str, t_token_list *list, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] && !isspace(str[*i]) && !is_quote(str[*i])
		&& str[*i] != '|' && str[*i] != '<' && str[*i] != '>')
		(*i)++;
	if (*i > start)
		token_list_add(list, TOKEN_WORD, ft_substr(str, start, *i - start));
	return (0);
}

void	tokenize_input(const char *str, t_token_list *list)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (isspace(str[i]))
			i++;
		else if (is_quote(str[i]))
			i += handle_quote(str, list, i);
		else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			i += handle_special_char(str[i], list);
		else
			handle_word(str, list, &i);
	}
}
