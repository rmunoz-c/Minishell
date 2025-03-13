/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:32:13 by enogueir          #+#    #+#             */
/*   Updated: 2025/03/13 19:32:53 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/tokenizer.h"

int	is_special_char(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

size_t	handle_special_char(char c, t_token **tokens, size_t *token_count)
{
	if (c == '|')
		add_token(tokens, token_count, TOKEN_PIPE, "|");
	else if (c == '>')
		add_token(tokens, token_count, TOKEN_REDIRECT_OUT, ">");
	else if (c == '<')
		add_token(tokens, token_count, TOKEN_REDIRECT_IN, "<");
	return (1);
}

size_t	handle_word(const char *str, t_token **tokens, size_t *token_count)
{
	size_t	len;
	char	*expanded;

	len = 0;
	expanded = NULL;
	while (str[len] && !isspace(str[len]) && !is_special_char(str[len]))
	{
		if (str[len] == '$' && str[len + 1] == '?')
		{
			expanded = expand_exit_status();
			break ;
		}
		else if (str[len] == '$' && str[len + 1])
		{
			expanded = expand_variable(str + len + 1);
			break ;
		}
		len++;
	}
	if (expanded)
		add_token(tokens, token_count, TOKEN_WORD, expanded);
	else
		add_token(tokens, token_count, TOKEN_WORD, str);
	free(expanded);
	return (len - 1);
}

size_t	handle_quote(const char *str, t_token **tokens, size_t *token_count,
		char quote)
{
	size_t	len;
	int		expand;

	expand = (quote == '"');
	len = 1;
	while (str[len] && str[len] != quote)
		len++;
	if (str[len] == '\0')
	{
		add_token(tokens, token_count, TOKEN_ERROR, "Unclosed quote");
		return (len);
	}
	len++;
	if (expand)
		add_token(tokens, token_count, TOKEN_ENV_VAR, str + 1);
	else
		add_token(tokens, token_count, TOKEN_WORD, str + 1);
	return (len - 1);
}
