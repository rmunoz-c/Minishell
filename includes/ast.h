/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:22:04 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/10 18:21:58 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <stddef.h>
# include "minishell.h"

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT
}	t_node_type;

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
}	t_redir;

typedef struct s_ast_node
{
	t_node_type			type;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_redir			*redirs;
	size_t			redir_count;
}	t_ast_node;

t_ast_node	*ast_node_create(t_node_type type, char **args);
void		ast_node_free(t_ast_node *node);

#endif