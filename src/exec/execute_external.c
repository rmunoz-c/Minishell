/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:10:08 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/08 21:30:22 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/execute.h"
#include "../../includes/minishell.h"
#include <stdio.h>

void	execute_external(char *cmd_path, char **args, char **env)
{
	if (execve(cmd_path, args, env) == -1)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
}

void	handle_external_command(char **args, char **env)
{
	char	**paths;
	char	*cmd_path;

	if (!args[0])
		exit(EXIT_FAILURE);
	if (ft_strchr(args[0], '/'))
		cmd_path = ft_strdup(args[0]);
	else
	{
		paths = get_paths_from_env(env);
		cmd_path = find_executable(args[0], paths);
		ft_free_array(paths);
	}
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	if (access(cmd_path, X_OK) != 0)
	{
		perror("minishell");
		free(cmd_path);
		exit(126);
	}
	execute_external(cmd_path, args, env);
}
