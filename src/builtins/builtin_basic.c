/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_basic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:24:25 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/16 22:31:51 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_flags(char **argv, int *i)
{
	int		new_line;
	size_t	j;

	new_line = 1;
	while (argv[*i] && argv[*i][0] == '-' && argv[*i][1] == 'n')
	{
		j = 1;
		while (argv[*i][j] == 'n')
			j++;
		if (argv[*i][j] != '\0')
			break ;
		new_line = 0;
		(*i)++;
	}
	return (new_line);
}

int	builtin_echo(char **argv)
{
	int	i;
	int	n_flag;

	i = 0;
	argv++;
	n_flag = process_flags(argv, &i);
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1])
			ft_printf(" ");
		i++;
	}
	if (n_flag)
		write(1, "\n", 1);
	return (0);
}

int	builtin_pwd(void)
{
	char	buffer[4096];

	if (getcwd(buffer, sizeof(buffer)))
	{
		printf("%s\n", buffer);
		return (0);
	}
	perror("pwd");
	return (1);
}

int	builtin_env(t_envp *envp, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (envp[i].value)
		{
			printf("%s=%s\n", envp[i].key, envp[i].value);
		}
		i++;
	}
	return (0);
}
