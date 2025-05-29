/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:31:21 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/28 19:07:45 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		is_builtin(char *cmd);
int		execute_builtin(char **args, t_minishell *shell);

t_envp	*envp_struct_realloc_with(t_envp *env, size_t *env_count, 
            const char *key, const char *value);
void	update_env(t_minishell *shell, const char *key, const char *value);


int     builtin_echo(char **args, t_minishell *shell);
int	    builtin_pwd(t_minishell *shell);
int 	builtin_env(t_minishell *shell);
int	    builtin_cd(char **args, t_minishell *shell);
int		builtin_export(char **args, t_minishell *shell);
int		builtin_unset(char **args, t_minishell *shell);
int	    builtin_exit(char **args, t_minishell *shell);

t_envp	*dup_envp_struct(char **envp, size_t *out_count);

#endif
