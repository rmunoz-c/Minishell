/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:18:46 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/12 18:11:19 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/tokenizer.h"
#include "../includes/expander.h"
#include "../includes/parser.h"
#include "../includes/execute.h"

static const char *token_type_str[] = {
	[TOKEN_WORD] = "WORD",
	[TOKEN_PIPE] = "PIPE",
	[TOKEN_REDIRECT_IN] = "<",
	[TOKEN_REDIRECT_OUT] = ">",
	[TOKEN_REDIRECT_IN_DBL] = "<<",
	[TOKEN_REDIRECT_OUT_DBL] = ">>",
	[TOKEN_ERROR] = "ERROR",
	[TOKEN_EOF] = "EOF"
};

static void	print_tokens(t_token_list *list)
{
	size_t	i = 0;
	while (i < list->size)
	{
		printf("[%s] \"%s\" (len: %zu, sq: %d, dq: %d)\n",
			token_type_str[list->array[i].type],
			list->array[i].value,
			list->array[i].length,
			list->array[i].in_single_quote,
			list->array[i].in_double_quote);
		i++;
	}
}

static void	print_indent(int depth)
{
	while (depth-- > 0)
		printf("  ");
}

static void	print_redirs(t_ast_node *node, int depth)
{
	size_t	i = 0;
	while (i < node->redir_count)
	{
		print_indent(depth);
		printf("redir: ");
		if (node->redirs[i].type == TOKEN_REDIRECT_IN)
			printf("< ");
		else if (node->redirs[i].type == TOKEN_REDIRECT_OUT)
			printf("> ");
		else if (node->redirs[i].type == TOKEN_REDIRECT_IN_DBL)
			printf("<< ");
		else if (node->redirs[i].type == TOKEN_REDIRECT_OUT_DBL)
			printf(">> ");
		printf("%s\n", node->redirs[i].filename);
		i++;
	}
}

static void	print_ast(t_ast_node *node, int depth)
{
	int		i;

	if (!node)
		return ;
	print_indent(depth);
	if (node->type == NODE_PIPE)
		printf("PIPE\n");
	else if (node->type == NODE_COMMAND)
	{
		printf("CMD:");
		i = 0;
		while (node->args && node->args[i])
			printf(" %s", node->args[i++]);
		printf("\n");
		print_redirs(node, depth + 1);
	}
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	t_token_list	list;
	t_ast_node	*ast;
	char		*line;

	(void)argc;
	(void)argv;
	shell.envp = dup_envp_struct(envp, &shell.env_count);
	shell.exit_status = 0;
	while (1)
	{
		line = readline("minishell_test > ");
		if (!line)
			break;
		if (*line)
			add_history(line);
		token_list_init(&list);
		tokenize_input(line, &list);
		expand_token_list(&list, &shell);
		printf("TOKENS:\n");
		print_tokens(&list);
		ast = parse_input(&list);
		if (!ast)
			printf("Error: parser returned NULL\n");
		else
		{
			printf("\nAST:\n");
			print_ast(ast, 0);
			if (process_heredocs(ast, &shell) < 0)
			{
				ast_node_free(ast);
				token_list_free(&list);
				free(line);
				continue;
			}
			execute_node(ast, &shell);
			ast_node_free(ast);
		}
		token_list_free(&list);
		free(line);
	}
	free_envp(shell.envp, shell.env_count);
	return (0);
}
