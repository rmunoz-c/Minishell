/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:04:39 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/28 18:43:17 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "token_list.h"

/*expander_build.c*/
char	*build_expanded_word(const char *str, size_t *pos, t_minishell *shell);

/*expander_utils.c*/
char	*expand_exit_status(t_minishell *shell);
char	*expand_variable(const char *var);
int		append_char_to_result(char c, char **result);
int		process_expansion(const char *str, size_t *pos, char **res,
			t_minishell *shell);
int		expand_and_join(const char *str, size_t *pos, char **result,
			t_minishell *shell);

/*expander.c*/
char	*get_env_value(const char *name, t_envp *env, size_t count);
char	*expand_dollar(const char *str, size_t *i, t_minishell *shell);
char	*expand_string(const char *str, t_minishell *shell);
void	expand_token_list(t_token_list *list, t_minishell *shell);
char	*expand_inside_string(const char *substr, t_minishell *shell);

#endif
