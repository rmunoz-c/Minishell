/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:18:46 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/20 20:21:47 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"
#include "../includes/expander.h"
#include "../includes/parser.h"
#include "../includes/execute.h"
#include "../includes/signals.h"

static void	handle_extra_arguments(char **argv)
{
	ft_printf("Error: minishell no acepta argumentos adicionales\n");
	ft_printf("Uso: %s\n", argv[0]);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*shell;

	if (argc != 1)
		handle_extra_arguments(argv);
	shell = initialize_shell(envp);
	if (!shell)
		return (1);
	setup_signals();
	run_shell_loop(shell);
	if (shell->envp)
		free_envp(shell->envp, shell->env_count);
	rl_clear_history();
	free(shell);
	return (0);
}
