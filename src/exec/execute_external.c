/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:10:08 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/28 19:16:38 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/execute.h"
#include "../../includes/minishell.h"
#include "../../includes/expander.h"
#include <stdio.h>


void execute_external(char *cmd_path, char **args, char **env)
{
    execve(cmd_path, args, env);
    int err = errno; 
    perror("minishell");
    free(cmd_path);
    free_flat_env(env);
    _exit(err & 0xFF);
}

static char **flatten_envp(t_envp *envp, size_t count)
{
    size_t i;
    char **flat;

    flat = malloc(sizeof(char *) * (count + 1));
    if (!flat)
        _exit(EXIT_FAILURE);
    i = 0;
    while (i < count)
    {
        flat[i] = malloc(ft_strlen(envp[i].key)
                         + ft_strlen(envp[i].value) + 2);
        if (!flat[i])
            _exit(EXIT_FAILURE);
        ft_strlcpy(flat[i], envp[i].key, ft_strlen(envp[i].key) + 1);
        ft_strlcat(flat[i], "=", ft_strlen(envp[i].key)
                              + ft_strlen(envp[i].value) + 2);
        ft_strlcat(flat[i], envp[i].value,
                   ft_strlen(envp[i].key)
                 + ft_strlen(envp[i].value) + 2);
        i++;
    }
    flat[i] = NULL;
    return (flat);
}

static char **get_paths_from_shell(t_minishell *shell)
{
    char   *path_val;
    char   **paths;

    path_val = get_env_value("PATH", shell->envp, shell->env_count);
    if (!path_val || *path_val == '\0')
        _exit(127);
    paths = ft_split(path_val, ':');
    free(path_val);
    if (!paths)
        _exit(EXIT_FAILURE);
    return (paths);
}

void handle_external_command(char **args, t_minishell *shell)
{
    char   **paths;
    char   *cmd_path;
    char   **flat_env;

    if (!args[0])
        _exit(EXIT_FAILURE);
    if (ft_strchr(args[0], '/'))
        cmd_path = ft_strdup(args[0]);
    else
    {
        paths = get_paths_from_shell(shell);
        cmd_path = find_executable(args[0], paths);
        ft_free_array(paths);
    }
    if (!cmd_path)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(args[0], 2);
        ft_putendl_fd(": command not found", 2);
        _exit(127);
    }
    if (access(cmd_path, X_OK) != 0)
    {
        perror("minishell");
        free(cmd_path);
        _exit(126);
    }
    flat_env = flatten_envp(shell->envp, shell->env_count);
    execute_external(cmd_path, args, flat_env);
}
