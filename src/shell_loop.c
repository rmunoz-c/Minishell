/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:27:45 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/16 23:23:33 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"
#include "../includes/expander.h"
#include "../includes/parser.h"
#include "../includes/execute.h"
#include "../includes/signals.h"

volatile sig_atomic_t	g_interactive = 1;

static char	*get_input_line(int interactive)
{
	char	*raw_line;

	if (interactive)
	{
		g_interactive = 1;
		raw_line = readline("minishell-> ");
	}
	else
	{
		g_interactive = 0;
		raw_line = get_next_line(STDIN_FILENO);
	}
	return (raw_line);
}

static int	process_raw_line(char **raw_line)
{
	size_t	len;

	if (!raw_line || !*raw_line)
		return (1);
	len = ft_strlen(*raw_line);
	if (len > 0 && (*raw_line)[len - 1] == '\n')
		(*raw_line)[len - 1] = '\0';
	if (is_line_empty(*raw_line))
	{
		free(*raw_line);
		return (1);
	}
	return (0);
}

static void	execute_command(t_minishell *shell, t_ast_node *ast)
{
	g_interactive = 0;
	if (ast && ast->type == NODE_COMMAND
		&& ast->args && ast->args[0]
		&& is_builtin(ast->args[0]))
		execute_builtin(ast, shell);
	else if (ast)
		execute_node(ast, shell);
	g_interactive = 1;
	setup_signals();
}

static void	process_command_line(t_minishell *shell, char *line)
{
	t_token_list	list;
	t_ast_node		*ast;
	int				status;

	(token_list_init(&list), tokenize_input(line, &list));
	expand_token_list(&list, shell);
	ast = parse_input(&list);
	if (!ast)
	{
		(ft_printf("Error: parser returned NULL\n"), token_list_free(&list));
		return ;
	}
	status = process_heredocs(ast, shell);
	if (status < 0 || status == 130)
	{
		free_and_return(ast, &list);
		return ;
	}
	if (ast->type == NODE_COMMAND
		&& (ast->args == NULL || ast->args[0] == NULL))
	{
		free_and_return(ast, &list);
		return ;
	}
	(execute_command(shell, ast), free_and_return(ast, &list));
}

void	run_shell_loop(t_minishell *shell)
{
	char			*raw_line;
	char			*line;
	int				interactive;

	interactive = isatty(STDIN_FILENO);
	while (1)
	{
		raw_line = get_input_line(interactive);
		if (!raw_line)
			break ;
		if (process_raw_line(&raw_line))
			continue ;
		if (interactive)
			add_history(raw_line);
		line = raw_line;
		process_command_line(shell, line);
		free(line);
	}
	if (interactive)
	{
		clear_history();
		ft_printf("exit\n");
	}
}
