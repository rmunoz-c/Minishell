/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:47:08 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/13 18:35:50 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/minishell.h"

t_ast_node	*ast_node_create(t_node_type type, char **args)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = args;
	node->left = NULL;
	node->right = NULL;
	node->redirs = NULL;
	node->redir_count = 0;
	return (node);
}

void	ast_node_free(t_ast_node *node)
{
	size_t	i;

	if (!node)
		return ;
	if (node->args)
	{
		i = 0;
		while (node->args[i])
			free(node->args[i++]);
		free(node->args);
	}
	if (node->redirs)
	{
		i = 0;
		while (i < node->redir_count)
			free(node->redirs[i++].filename);
		free(node->redirs);
	}
	ast_node_free(node->left);
	ast_node_free(node->right);
	free(node);
}

void	free_redirs_partial(t_redir *array, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(array[i].filename);
		i++;
	}
	free(array);
}

static int	copy_existing_redirs(t_redir *dst, t_redir *src, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		dst[i].type = src[i].type;
		dst[i].filename = ft_strdup(src[i].filename);
		dst[i].fd = src[i].fd;
		dst[i].quoted = src[i].quoted;
		if (!dst[i].filename)
			return (free_redirs_partial(dst, i), 0);
		i++;
	}
	return (1);
}

int	add_redirection(t_ast_node *cmd_node, t_token_type type,
	const char *filename, int quoted)
{
	t_redir	*new_array;
	size_t	count;

	count = cmd_node->redir_count;
	new_array = malloc(sizeof(t_redir) * (count + 1));
	if (!new_array)
		return (0);
	if (!copy_existing_redirs(new_array, cmd_node->redirs, count))
		return (0);
	new_array[count].type = type;
	new_array[count].filename = ft_strdup(filename);
	new_array[count].fd = -1;
	new_array[count].quoted = quoted;
	if (!new_array[count].filename)
		return (free_redirs_partial(new_array, count), 0);
	free(cmd_node->redirs);
	cmd_node->redirs = new_array;
	cmd_node->redir_count++;
	return (1);
}
