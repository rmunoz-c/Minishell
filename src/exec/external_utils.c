/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:00:03 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/12 21:30:39 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/minishell.h"

char	**get_paths_from_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i] || !env[i][5])
		return (NULL);
	return (ft_split(env[i] + 5, ':'));
}

char	*find_executable(char *cmd, char **paths)
{
	char	*full_path;
	int		i;

	if (!paths || !cmd)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoinfree(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*resolve_cmd_path(t_ast_node *node, char **flat_env)
{
	char	**paths;
	char	*cmd_path;

	if (!node || !node->args || !node->args[0])
		return (NULL);
	if (ft_strchr(node->args[0], '/'))
		return (ft_strdup(node->args[0]));
	paths = get_paths_from_env(flat_env);
	if (!paths)
		return (NULL);
	cmd_path = find_executable(node->args[0], paths);
	ft_free_array(paths);
	return (cmd_path);
}
