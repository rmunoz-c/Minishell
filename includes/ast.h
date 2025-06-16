/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:22:04 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/13 18:43:05 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "token_list.h"
# include <stddef.h>

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
}						t_node_type;

typedef struct s_redir
{
	t_token_type		type;
	char				*filename;
	int					fd;
	int					quoted;
}						t_redir;

typedef struct s_ast_node
{
	t_node_type			type;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_redir				*redirs;
	size_t				redir_count;
}						t_ast_node;

t_ast_node				*ast_node_create(t_node_type type, char **args);
void					ast_node_free(t_ast_node *node);
void					free_redirs_partial(t_redir *array, size_t count);
int						add_redirection(t_ast_node *cmd_node, t_token_type type,
							const char *filename, int quoted);

#endif