/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:16:19 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/17 21:41:48 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/minishell.h"
#include "../../includes/execute.h"

static int	open_and_dup(const char *filename, int flags, int std_fd)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd < 0)
		return (perror(filename), -1);
	if (dup2(fd, std_fd) < 0)
		return (perror("dup2"), close(fd), -1);
	close(fd);
	return (0);
}

static int	apply_heredoc(t_ast_node *node, size_t index, size_t last)
{
	int	fd;

	fd = node->redirs[index].fd;
	if (fd >= 0)
	{
		if (index == last && dup2(fd, STDIN_FILENO) < 0)
			return (perror("dup2 heredoc final"), close(fd), -1);
		close(fd);
		node->redirs[index].fd = -1;
	}
	return (0);
}

static size_t	get_last_heredoc_index(t_ast_node *node)
{
	size_t	i;
	size_t	last;

	i = 0;
	last = (size_t)-1;
	while (i < node->redir_count)
	{
		if (node->redirs[i].type == TOKEN_REDIRECT_IN_DBL)
			last = i;
		i++;
	}
	return (last);
}

static int	apply_other_redirs(t_ast_node *node, size_t i)
{
	if (node->redirs[i].type == TOKEN_REDIRECT_IN)
		return (open_and_dup(node->redirs[i].filename, O_RDONLY, STDIN_FILENO));
	if (node->redirs[i].type == TOKEN_REDIRECT_OUT)
		return (open_and_dup(node->redirs[i].filename,
				O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO));
	if (node->redirs[i].type == TOKEN_REDIRECT_OUT_DBL)
		return (open_and_dup(node->redirs[i].filename,
				O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO));
	return (0);
}

int	setup_redirections(t_ast_node *node)
{
	size_t	i;
	size_t	last_heredoc_index;

	last_heredoc_index = get_last_heredoc_index(node);
	i = 0;
	while (i < node->redir_count)
	{
		if (node->redirs[i].type == TOKEN_REDIRECT_IN_DBL)
		{
			if (apply_heredoc(node, i, last_heredoc_index) < 0)
				return (-1);
		}
		else if (apply_other_redirs(node, i) < 0)
			return (-1);
		i++;
	}
	return (0);
}
