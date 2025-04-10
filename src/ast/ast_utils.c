/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:17:26 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/10 18:18:21 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/minishell.h"
#include "../../libft/libft.h"

int	add_redirection(t_ast_node *cmd_node, t_token_type type, const char *filename)
{
	t_redir	*new_array;
	size_t	i;

	new_array = (t_redir *)malloc(sizeof(t_redir) * (cmd_node->redir_count + 1));
	if (!new_array)
		return (0);
	i = 0;
	while (i < cmd_node->redir_count)
	{
		new_array[i].type = cmd_node->redirs[i].type;
		new_array[i].filename = cmd_node->redirs[i].filename;
		i++;
	}
	new_array[i].type = type;
	new_array[i].filename = ft_strdup(filename);
	if (!new_array[i].filename)
	{
		free(new_array);
		return (0);
	}
	free(cmd_node->redirs);
	cmd_node->redirs = new_array;
	cmd_node->redir_count++;
	return (1);
}
