/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:14:04 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/08 19:14:12 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/minishell.h"
#include "../../libft/libft.h"

static void	free_node_args(t_ast_node *node)
{
	if (node->args)
	{
		ft_free_array(node->args);
		node->args = NULL;
	}
}

static void	free_node_redirs(t_ast_node *node)
{
	size_t	i;

	if (!node->redirs)
		return;
	i = 0;
	while (i < node->redir_count)
	{
		if (node->redirs[i].filename)
			free(node->redirs[i].filename);
		i++;
	}
	free(node->redirs);
	node->redirs = NULL;
}

static void	free_node_children(t_ast_node *node)
{
	if (node->left)
	{
		ast_node_free(node->left);
		node->left = NULL;
	}
	if (node->right)
	{
		ast_node_free(node->right);
		node->right = NULL;
	}
}

void	ast_node_free(t_ast_node *node)
{
	if (!node)
		return;
	free_node_args(node);
	free_node_redirs(node);
	free_node_children(node);
	free(node);
}
