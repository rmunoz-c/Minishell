/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:35:40 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/16 22:33:38 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ast.h"
#include "../../includes/expander.h"

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	close(0);
	g_interactive = 1;
}

static int	process_heredoc_loop(const char *delimiter, int write_fd,
									t_minishell *shell, int expand)
{
	char	*line;
	char	*processed;
	size_t	len;

	while (1)
	{
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || g_interactive)
			return (-1);
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, delimiter) == 0)
			return (free(line), 0);
		if (expand == 1)
			processed = expand_string(line, shell);
		else
			processed = ft_strdup(line);
		if (processed == NULL)
			return (free(line), -1);
		write(write_fd, processed, ft_strlen(processed));
		write(write_fd, "\n", 1);
		(free(line), free(processed));
	}
}

int	read_heredoc(const char *delimiter,
					int *heredoc_fd,
					t_minishell *shell,
					int expand)
{
	int	save_stdin;
	int	ret;

	save_stdin = dup(STDIN_FILENO);
	g_interactive = 0;
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	if (pipe(heredoc_fd) == -1)
		return (-1);
	ret = process_heredoc_loop(delimiter, heredoc_fd[1], shell, expand);
	close(heredoc_fd[1]);
	if (ret == -1)
	{
		close(heredoc_fd[0]);
		dup2(save_stdin, STDIN_FILENO);
		close(save_stdin);
		signal(SIGINT, handle_parent_signal);
		signal(SIGQUIT, SIG_IGN);
		return (-1);
	}
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	signal(SIGINT, handle_parent_signal);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

static int	process_command_heredocs(t_ast_node *node, t_minishell *shell)
{
	size_t	i;
	int		fd[2];
	int		expand;
	int		ret;

	i = 0;
	while (i < node->redir_count)
	{
		if (node->redirs[i].type == TOKEN_REDIRECT_IN_DBL)
		{
			expand = (node->redirs[i].quoted == 0);
			ret = read_heredoc(node->redirs[i].filename, fd, shell, expand);
			if (ret == -1)
			{
				if (g_interactive)
					return (130);
				return (-1);
			}
			if (ret != 0)
				return (-1);
			node->redirs[i].fd = fd[0];
		}
		i++;
	}
	return (0);
}

int	process_heredocs(t_ast_node *node, t_minishell *shell)
{
	int	ret;

	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
	{
		ret = process_command_heredocs(node, shell);
		if (ret != 0)
			return (ret);
	}
	if (node->left)
	{
		ret = process_heredocs(node->left, shell);
		if (ret != 0)
			return (ret);
	}
	if (node->right)
	{
		ret = process_heredocs(node->right, shell);
		if (ret != 0)
			return (ret);
	}
	return (0);
}
