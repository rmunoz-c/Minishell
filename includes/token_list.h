/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:03:11 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/29 21:40:08 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

# include "minishell.h"
# include <stddef.h>

typedef struct s_token_list
{
	t_token	*array;
	size_t	size;
	size_t	capacity;
}			t_token_list;

void		token_list_init(t_token_list *list);
void		token_list_free(t_token_list *list);
int			token_list_add_token(t_token_list *list, t_token *token);

#endif
