/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:04:06 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/17 22:07:02 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_ast_node *node, t_minishell *shell)
{
	int	code;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!node->args[1])
	{
		code = shell->exit_status;
		(free_ast(node), free_all(shell));
		exit(code);
	}
	if (!is_numeric(node->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(node->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		(free_ast(node), free_all(shell));
		exit(255);
	}
	if (node->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	code = ft_atoi(node->args[1]);
	(free_ast(node), free_all(shell));
	exit((unsigned char)code);
}
