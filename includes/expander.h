/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:04:39 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/05 19:03:36 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "token_list.h"
# include "minishell.h"

void	expand_token_list(t_token_list *list, t_minishell *shell);
char	*expand_string(const char *str, t_minishell *shell);

void	split_expanded_token(t_token_list *list);

#endif
