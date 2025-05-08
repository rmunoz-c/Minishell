/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:17:26 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/08 22:23:30 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/minishell.h"
#include "../../libft/libft.h"

static void	free_redirs_partial(t_redir *redirs, size_t count)
{
	while (count > 0)
	{
		count--;
		free(redirs[count].filename);
	}
	free(redirs);
}

static int	copy_old_redirections(t_redir *dst, t_redir *src, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		dst[i].type = src[i].type;
		if (!src[i].filename)
			return (0);
		dst[i].filename = ft_strdup(src[i].filename);
		if (!dst[i].filename)
			return (0);
		i++;
	}
	return (1);
}

int	add_redirection(t_ast_node *cmd_node, t_token_type type,
		const char *filename)
{
	t_redir	*new_array;
	size_t	count;
	
	count = cmd_node->redir_count;
	new_array = malloc(sizeof(t_redir) * (count + 1));
	if (!new_array)
		return (0);
	if (count > 0 && !copy_old_redirections(new_array,
			cmd_node->redirs, count))
	{
		free_redirs_partial(new_array, count);
		cmd_node->redirs = NULL;
		cmd_node->redir_count = 0;
		return (0);
	}
	new_array[count].type = type;
	new_array[count].filename = ft_strdup(filename);
	if (!new_array[count].filename)
	{
		free_redirs_partial(new_array, count);
		cmd_node->redirs = NULL; // ¡Esto también es clave!
		cmd_node->redir_count = 0;
		return (0);
	}
	new_array[count].fd = -1;
	if (cmd_node->redirs)
		free(cmd_node->redirs);
	cmd_node->redirs = new_array;
	cmd_node->redir_count++;
	return (1);
}
