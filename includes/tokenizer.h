/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:04:04 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/03 18:22:56 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "token_list.h"

/*quote_handler.c*/
size_t	handle_quote_token(const char *str, t_token_list *list, size_t start);

/*tokenizer_utils.c*/
int		is_special_char(char c);
int		is_quote(char c);
int		is_whitespace(char c);

/*tokenizer.c*/
size_t	handle_quote(const char *str, t_token_list *list, size_t start);
size_t	handle_special_char(char c, t_token_list *list);
size_t	handle_word(const char *str, t_token_list *list, size_t *i);
void	tokenize_input(const char *str, t_token_list *list);


#endif
