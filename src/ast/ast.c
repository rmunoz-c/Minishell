/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:23:48 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/10 18:28:23 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../libft/libft.h"

static void	free_str_array_partial(char **arr, size_t used)
{
	while (used > 0)
	{
		used--;
		free(arr[used]);
	}
	free(arr);
}

static char	**dup_str_array(char **args)
{
	size_t	count;
	size_t	i;
	char	**copy;

	count = 0;
	while (args && args[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(args[i]);
		if (!copy[i])
		{
			free_str_array_partial(copy, i);
			return (NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

t_ast_node	*ast_node_create(t_node_type type, char **args)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->args = dup_str_array(args);
	if (!node->args && args && args[0])
	{
		free(node);
		return (NULL);
	}
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
			(free(node->args[i]), i++);
		free(node->args);
	}
	if (node->redirs)
	{
		i = 0;
		while (i < node->redir_count)
			(free(node->redirs[i].filename), i++);
		free(node->redirs);
	}
	ast_node_free(node->left);
	ast_node_free(node->right);
	free(node);
}
