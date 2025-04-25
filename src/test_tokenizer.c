/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:18:59 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/25 19:38:29 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/minishell.h"
#include "../includes/token_list.h"
#include "../includes/tokenizer.h"
#include "../includes/expander.h"
#include "../includes/ast.h"
#include "../includes/parser.h"
#include "../libft/libft.h"
#include "../includes/execute.h"

static void	print_redirs(t_redir *redirs, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (redirs[i].type == TOKEN_REDIRECT_IN)
			printf("( < %s ) ", redirs[i].filename);
		else if (redirs[i].type == TOKEN_REDIRECT_OUT)
			printf("( > %s ) ", redirs[i].filename);
		else if (redirs[i].type == TOKEN_REDIRECT_OUT_DBL)
			printf("( >> %s ) ", redirs[i].filename);
		else if (redirs[i].type == TOKEN_REDIRECT_IN_DBL)
			printf("( << %s ) ", redirs[i].filename);
		i++;
	}
}

static void	print_node(t_ast_node *node)
{
	size_t	i;

	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
	{
		print_redirs(node->redirs, node->redir_count);
		printf("{ ");
		i = 0;
		while (node->args && node->args[i])
		{
			printf("%s ", node->args[i]);
			i++;
		}
		printf("}");
	}
	else if (node->type == NODE_PIPE)
	{
		print_node(node->left);
		printf("\n|\n");
		print_node(node->right);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_token_list	list;
	t_ast_node		*ast;
	t_minishell		shell;
	//size_t 			i = 0;

	(void)argc;
	(void)argv;
	shell.envp = envp;

	while (1)
{
	line = readline("PuenteCuatroShell > ");
	if (!line)
		break ;
	add_history(line);
	token_list_init(&list);
	tokenize_input(line, &list);
	expand_token_list(&list);
	ast = parse_input(&list);

	if (ast)
	{
		print_node(ast);
		printf("\n");
		if (ast->type == NODE_COMMAND)
			execute_node(ast, &shell);
		ast_node_free(ast);
	}

	token_list_free(&list);
	free(line);
}

	return (0);
}


/*(int	main(void)
{
	t_token	*tokens;
	size_t	token_count;
	size_t	i;
	char	*input;

	while (1)
	{
		input = readline("PuenteCuatroShell > ");
		add_history(input);
		tokens = tokenize(input, &token_count);
		if (!tokens)
			return (printf("Error en el tokenizador\n"), 1);
		i = 0;
		while (i < token_count && tokens[i]->type != TOKEN_EOF)
		{
			printf("Token [%s], Tipo: %d, Longitud: %zu\n", tokens[i]->value,
				tokens[i]->type, tokens[i]->length);
			i++;
		}
		free_tokens(tokens, token_count);
		free(input);
	}
	return (0);
}*/

// input = "echo hola $USER que tal estas? "$HOME" d $PWD";
