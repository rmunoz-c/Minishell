/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:31:21 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/08 19:31:36 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	is_builtin(char *cmd);
int	execute_builtin(char **args, t_minishell *shell);

int	builtin_echo(char **args);
int	builtin_pwd(void);
int	builtin_env(char **envp);
int	builtin_cd(char **args, t_minishell *shell);
int	builtin_export(char **args, t_minishell *shell);
int	builtin_unset(char **args, t_minishell *shell);
int	builtin_exit(char **args);

#endif
