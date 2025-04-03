/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:04:39 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/03 18:29:55 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "token_list.h"

/*expander_build.c*/
int		handle_dollar_quote(const char *str, size_t *pos, char **res);
char	*build_expanded_word(const char *str, size_t *pos);

/*expander_utils.c*/
char	*expand_exit_status(void);
char	*expand_variable(const char *var);
int 	append_char_to_result(char c, char **result);
int		process_expansion(const char *str, size_t *pos, char **res);
int		expand_and_join(const char *str, size_t *pos, char **result);

/*expander.c*/
char	*get_env_value(const char *name);
char	*expand_dollar(const char *str, size_t *i);
char	*expand_string(const char *str);
void	expand_token_list(t_token_list *list);
char	*expand_inside_string(const char *substr);

#endif
