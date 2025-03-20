/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:07:35 by enogueir          #+#    #+#             */
/*   Updated: 2025/03/19 10:29:39 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	handle_special_char(char c, t_token **tokens, size_t *token_count)
{
	if (c == '|')
		add_token(&tokens, token_count, TOKEN_PIPE, "|");
	else if (c == '>')
		add_token(&tokens, token_count, TOKEN_REDIRECT_OUT, ">");
	else if (c == '<')
		add_token(&tokens, token_count, TOKEN_REDIRECT_IN, "<");
	return (1);
}

static int	expand_tokens(t_token ***tokens, size_t *capacity)
{
    size_t	new_capacity;
    t_token	**new_tokens;
    size_t	i;

    new_capacity = (*capacity) * 2;
    new_tokens = malloc(new_capacity * sizeof(t_token *));
    if (!new_tokens)
        return (0);
    i = 0;
    while (i < *capacity)
    {
        new_tokens[i] = (*tokens)[i];
        i++;
    }
    free(*tokens);
    *tokens = new_tokens;
    *capacity = new_capacity;
    return (1);
}

static t_token	*create_token(t_token_type type, const char *value)
{
	t_token	*new_tok;
	size_t	len;

	len = 0;
	if (value)
		len = strlen(value);
	new_tok = malloc(sizeof(t_token));
	if (!new_tok)
		return (NULL);
	new_tok->type = type;
	new_tok->value = NULL;
	if (value)
		new_tok->value = ft_substr(value, 0, len);
	if (value && !new_tok->value)
	{
		free(new_tok);
		return (NULL);
	}
	new_tok->length = len;
	return (new_tok);
}

int	add_token(t_token ***tokens, size_t *token_count, t_token_type type,
		const char *value)
{
	static size_t	capacity = 8;
	
	if (!value || *value == '\0')
		return (0);
	if (*token_count >= capacity)
		if (!expand_tokens(tokens, &capacity))
			return (0);
	(*tokens)[*token_count] = create_token(type, value);
	if (!(*tokens)[*token_count])
		return (0);
	(*token_count)++;
	return (1);
}

t_token	**tokenize(const char *str, size_t *token_count)
{
	t_token	**tokens;
	size_t	i;

	*token_count = 0;
	tokens = malloc(sizeof(t_token *) * 8);
	if (!tokens)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (isspace(str[i]))
			i++;
		else if (is_special_char(str[i]))
			i += handle_special_char(str[i], tokens, token_count);
		else if (is_quote(str[i]))
			i += handle_quote(&str[i], tokens, token_count, str[i]);
		else
			i += handle_word(&str[i], tokens, token_count);
	}
	add_token(&tokens, token_count, TOKEN_EOF, NULL);
	return (tokens);	
}
