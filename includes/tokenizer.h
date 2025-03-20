/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:04:04 by enogueir          #+#    #+#             */
/*   Updated: 2025/03/13 19:28:57 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"

size_t	handle_special_char(char c, t_token **tokens, size_t *token_count);
t_token	**tokenize(const char *str, size_t *token_count);
int		add_token(t_token ***tokens, size_t *token_count, t_token_type type,
			const char *value);

int		is_special_char(char c);
int		is_quote(char c);
char	*expand_dollar(const char *str, size_t *pos);
size_t	handle_word(const char *str, t_token **tokens, size_t *token_count);
size_t	handle_quote(const char *str, t_token **tokens, size_t *token_count,
			char quote);

char	*build_expanded_word(const char *str, size_t *pos);

#endif
