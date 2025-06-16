/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:49:13 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/12 20:03:45 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !ft_isalpha(str[0]))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	export_print_all(t_envp *envp, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(envp[i].key, 1);
		if (envp[i].value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(envp[i].value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putchar_fd('\n', 1);
		i++;
	}
}

int	builtin_export(char **argv, t_minishell *sh)
{
	int	i;

	if (!argv[1])
	{
		export_print_all(sh->envp, sh->env_count);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		export_one(argv[i], sh);
		i++;
	}
	return (0);
}
