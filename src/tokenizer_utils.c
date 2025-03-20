/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:32:13 by enogueir          #+#    #+#             */
/*   Updated: 2025/03/19 11:18:22 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_special_char(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

/*char	*expand_dollar(const char *str, size_t *pos)
{
	char	*expanded;
	size_t	len;
	char	*var;

	expanded = NULL;
	(*pos)++;
	len = *pos;
	while (str[len] && ft_isalnum(str[len]))
		len++;
	var = ft_substr(str, *pos - 1, len);
	if (str[*pos] == '?')
		expanded = expand_exit_status();
	else
		expanded = expand_variable(var);
	while (str[*pos] && ft_isalnum(str[*pos]))
		(*pos)++;
	return (expanded);
}*/

char	*expand_dollar(const char *str, size_t *pos)
{
	char	*expanded;
	size_t	start;
	size_t	var_len;

	// Saltas el '$'
	(*pos)++;
	// Si es '$?', expandes exit status y avanzas uno más.
	if (str[*pos] == '?')
	{
		(*pos)++;
		return (expand_exit_status());
	}
	// Guardas posición inicial del nombre de variable
	start = *pos;
	while (str[*pos] && ft_isalnum(str[*pos]))
		(*pos)++;
	// Cantidad de chars del nombre
	var_len = *pos - start;
	// Si no había nada (ej. '$ hola'), expandes a ""
	if (var_len == 0)
		return (ft_strdup(""));
	// Copias solo el nombre sin '$'
	expanded = expand_variable(ft_substr(str, start, var_len));
	return (expanded);
}

/*size_t	handle_word(const char *str, t_token **tokens, size_t *token_count)
{
	size_t	len;
	size_t	word_len;
	char	*expanded;

	len = 0;
	expanded = NULL;
	while (str[len] && !isspace(str[len]) && !is_special_char(str[len]))
	{
		if (str[len] == '$' && str[len + 1])
		{
			expanded = expand_dollar(str, &len);
			break;
		}
		len++;
	}
	if (len == 0)
		return (1);
	word_len = len;
	if (!expanded)
		expanded = ft_substr(str, 0, word_len);
	if (!expanded)
		return (word_len);
	add_token(&tokens, token_count, TOKEN_WORD, expanded);
	free(expanded);
	return (word_len);
}*/

size_t	handle_word(const char *str, t_token **tokens, size_t *tc)
{
	size_t	pos;
	char	*word;
	size_t	result;

	pos = 0;
	word = build_expanded_word(str, &pos);
	if (!word)
		return (1);
	if (word[0] == '\0')
	{
		result = pos;
		free(word);
		if (pos == 0)
			return (1);
		return (result);
	}
	add_token(&tokens, tc, TOKEN_WORD, word);
	free(word);
	return (pos);
}


size_t	handle_quote(const char *str, t_token **tokens, size_t *token_count,
		char quote)
{
	size_t	len;
	char	*expanded_str;
	char 	*quoted_str;

	len = 1;
	while (str[len] && str[len] != quote)
		len++;
	if (str[len] != quote)
	{
		add_token(&tokens, token_count, TOKEN_ERROR, "Unclosed quote");
		return (len);
	}
	quoted_str = ft_substr(str, 1, len - 1);
	if (!quoted_str)
		return (len);
	if (quote == '"')
		expanded_str = expand_variable(quoted_str);
	else
		expanded_str = ft_strdup(quoted_str);
	if (expanded_str && *expanded_str)
		add_token(&tokens, token_count, TOKEN_WORD, expanded_str);
	free(expanded_str);
	free(quoted_str);
	return (len + 1);
}
