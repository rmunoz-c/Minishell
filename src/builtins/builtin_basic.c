/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_basic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:32:33 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/28 18:46:19 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/minishell.h"
#include "../../includes/expander.h"
#include "../../libft/libft.h"

int	builtin_echo(char **args, t_minishell *shell)
{
	int	i;
	int	newline;

	if (args[1] && ft_strcmp(args[1], "$?") == 0 && args[2] == NULL)
	{
		ft_putnbr_fd(shell->exit_status, 1);
		write(1, "\n", 1);
		return (0);
	}
	i = 1;
	newline = 1;
	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}

int	builtin_pwd(t_minishell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: pwd");
		shell->exit_status = 1;
		return (1);
	}
	ft_putendl_fd(cwd, 1);
	update_env(shell, "PWD", cwd);
	free(cwd);
	shell->exit_status = 0;
	return (0);
}


int builtin_env(t_minishell *shell)
{
    size_t i;

    i = 0;
    while (i < shell->env_count)
    {
        ft_putstr_fd(shell->envp[i].key, 1);
        ft_putstr_fd("=", 1);
        ft_putendl_fd(shell->envp[i].value, 1);
        i++;
    }
    shell->exit_status = 0;
    return (0);
}

