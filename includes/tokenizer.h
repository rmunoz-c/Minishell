/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:04:04 by enogueir          #+#    #+#             */
/*   Updated: 2025/03/27 20:26:16 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "token_list.h"

int		is_special_char(char c);
int		is_quote(char c);
char	*expand_dollar(const char *str, size_t *pos);
size_t	handle_word(const char *str, t_token_list *tokens);
size_t	handle_quote(const char *str, t_token_list *list, size_t start);
size_t	handle_special_char(char c, t_token_list *list);
char	*build_expanded_word(const char *str, size_t *pos);
char	*build_inside_string(const char *substr);
char	*expand_inside_string(const char *substr);
t_token	*tokenize(const char *str, size_t *count);
char	*build_inside_string(const char *substr);
int		expand_and_join(const char *str, size_t *pos, char **result);

#endif
