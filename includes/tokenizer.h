/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:04:04 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/12 21:34:40 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "token_list.h"

/*tokenizer_assign.c*/
int		try_merge_assignment_with_quote(const char *str, t_token_list *list,
			size_t *i);

/*tokenize_utils.c*/
int		is_special_char(char c);
int		is_quote(char c);
int		add_token(t_token_list *list, t_token_type type, char *text, int len);
int		add_token_quoted(t_token_list *list, t_token_data data);
size_t	handle_special_char(const char *str, t_token_list *list, size_t i);

/*tokenize.c*/
void	tokenize_input(const char *str, t_token_list *list);

#endif