/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:01:40 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/08 22:20:00 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ast.h"

int	read_heredoc(char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

void	process_heredocs(t_ast_node *node)
{
	size_t	i;

	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		process_heredocs(node->left);
		process_heredocs(node->right);
	}
	else if (node->type == NODE_COMMAND)
	{
		i = 0;
		while (i < node->redir_count)
		{
			if (node->redirs[i].type == TOKEN_REDIRECT_IN_DBL)
			{
				node->redirs[i].fd = read_heredoc(node->redirs[i].filename);
				if (node->redirs[i].fd < 0)
					exit(EXIT_FAILURE);
			}
			i++;
		}
	}
}
