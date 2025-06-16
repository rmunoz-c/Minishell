/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:31:21 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/16 19:05:05 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/*builtin_basic.c*/
int		builtin_echo(char **argv);
int		builtin_pwd(void);
int		builtin_env(t_envp *envp, size_t count);

/*builtin_envmod.c*/
int		builtin_cd(char **argv, t_minishell *shell);

/*builtin_exit.c*/
int		builtin_exit(char **argv, t_minishell *shell);

/*builtin_export_utils.c*/
int		export_update_existing(const char *arg, char *equal, size_t len,
			t_minishell *sh);
void	export_add_new(const char *arg, char *equal, size_t len,
			t_minishell *sh);
void	export_one(const char *arg, t_minishell *sh);

/*builtin_export.c*/
int		builtin_export(char **argv, t_minishell *sh);

/*builtin_unset.c*/
int		builtin_unset(char **args, t_minishell *shell);

#endif
