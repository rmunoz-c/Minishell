/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:11:19 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/20 20:32:41 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ast.h"
#include "../includes/minishell.h"
#include "../includes/token_list.h"

int	is_line_empty(const char *s)
{
	int	i;
	int	whitespace_count;

	if (!s || s[0] == '\0')
		return (1);
	i = 0;
	whitespace_count = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\v'
			|| s[i] == '\f' || s[i] == '\r')
			whitespace_count++;
		i++;
	}
	return (whitespace_count == i);
}

void	free_ast(t_ast_node *ast)
{
	if (ast)
		ast_node_free(ast);
}

void	free_and_return(t_ast_node *ast, t_token_list *list)
{
	if (ast)
		free_ast(ast);
	token_list_free(list);
	return ;
}

void	free_all(t_minishell *shell)
{
	if (!shell)
		return ;
	if (shell->tokens)
		token_list_free(shell->tokens);
	if (shell->envp)
		free_envp(shell->envp, shell->env_count);
	rl_clear_history();
}
