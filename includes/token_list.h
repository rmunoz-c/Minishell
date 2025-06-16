/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:03:11 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/12 21:33:46 by enogueir         ###   ########.fr       */
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

typedef struct s_assign_parts
{
	size_t	var_start;
	size_t	equal_pos;
	size_t	end;
}			t_assign_parts;

typedef struct s_token_data
{
	t_token_type	type;
	char			*text;
	int				length;
	char			quote;
}			t_token_data;

void		token_list_init(t_token_list *list);
void		token_list_free(t_token_list *list);
int			token_list_add_token(t_token_list *list, t_token *token);
void		token_list_insert(t_token_list *list, size_t index, t_token token);

#endif
