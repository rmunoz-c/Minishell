/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:07:35 by enogueir          #+#    #+#             */
/*   Updated: 2025/03/27 20:27:53 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"
#include "../libft/libft.h"

int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
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

size_t	handle_quote(const char *str, t_token_list *list, size_t start)
{
	size_t	len;
	char	quote;
	char	*quoted;
	char	*expanded;

	quote = str[start];
	len = start + 1;
	while (str[len] && str[len] != quote)
		len++;
	if (str[len] != quote)
	{
		token_list_add(list, TOKEN_ERROR, "Unclosed quote");
		return (len - start);
	}
	quoted = ft_substr(str, start + 1, (len - 1) - start);
	if (!quoted)
		return (len - start + 1);
	if (quote == '"')
		expanded = expand_inside_string(quoted);
	else
		expanded = ft_strdup(quoted);
	if (expanded && expanded[0])
		token_list_add(list, TOKEN_WORD, expanded);
	(free(quoted), free(expanded));
	return ((len - start) + 1);
}

size_t	handle_word(const char *str, t_token_list *tokens)
{
	size_t	pos;
	char	*word;

	pos = 0;
	word = build_expanded_word(str, &pos);
	if (!word)
		return (1);
	if (word[0] != '\0')
		token_list_add(tokens, TOKEN_WORD, word);
	free(word);
	if (pos == 0)
		return (1);
	return (pos);

}

t_token	*tokenize(const char *str, size_t *count)
{
	t_token_list	list;
	size_t			i;

	token_list_init(&list);
	i = 0;
	while (str[i])
	{
		if (isspace(str[i]))
			i++;
		else if (is_special_char(str[i]))
			i += handle_special_char(str[i], &list);
		else if (is_quote(str[i]))
			i += handle_quote(str, &list, i);
		else
			i += handle_word(str + i, &list);
	}
	token_list_add(&list, TOKEN_EOF, "");
	*count = list.size;
	return (list.array);
}
