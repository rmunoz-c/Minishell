/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:07:35 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/29 21:38:52 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/token_list.h"
#include "../../includes/tokenizer.h"
#include "../../includes/expander.h"
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
	{
		add_special_token(list, TOKEN_ERROR, "Unclosed quote", 15);
		return (1);
	}
	quoted = ft_substr(str, start + 1, len - start - 1);
	if (!quoted)
		return (len - start + 1);
	if (quote == '\'')
		add_special_token_quoted(list, TOKEN_WORD, quoted, len - start - 1);
	else
		add_special_token(list, TOKEN_WORD, quoted, len - start - 1);
	free(quoted);
	return (len - start + 1);
}

size_t	handle_special_char(const char *str, t_token_list *list, size_t i)
{
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
		{
			add_special_token(list, TOKEN_REDIRECT_OUT_DBL, ">>", 2);
			return (2);
		}
		add_special_token(list, TOKEN_REDIRECT_OUT, ">", 1);
		return (1);
	}
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
		{
			add_special_token(list, TOKEN_REDIRECT_IN_DBL, "<<", 2);
			return (2);
		}
		add_special_token(list, TOKEN_REDIRECT_IN, "<", 1);
		return (1);
	}
	if (str[i] == '|')
		return (add_special_token(list, TOKEN_PIPE, "|", 1), 1);
	return (1);
}

size_t	handle_word(const char *str, t_token_list *list, size_t *i,
					t_minishell *shell)
{
	size_t	start;
	char	*word;
	size_t	length;

	start = *i;
	while (str[*i] && !isspace(str[*i]) && !is_quote(str[*i])
		&& str[*i] != '|' && str[*i] != '<' && str[*i] != '>')
		(*i)++;
	if (*i > start)
	{
		word = build_expanded_word(str, &start, shell);
		if (!word)
			return (0);
		length = ft_strlen(word);
		add_special_token(list, TOKEN_WORD, word, length);
		free(word);
	}
	return (*i - start);
}


void	tokenize_input(const char *str, t_token_list *list, t_minishell *shell)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (isspace(str[i]))
			i++;
		else if (str[i] == '$'
			&& (str[i + 1] == '"' || str[i + 1] == '\''))
			i += handle_dollar_quote_token(str, list, i);
		else if (str[i] == '\'')
			i += handle_quote(str, list, i);
		else if (str[i] == '"')
			i += handle_quote(str, list, i);
		else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			i += handle_special_char(str, list, i);
		else
			handle_word(str, list, &i, shell);
	}
}
