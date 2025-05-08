/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:05:33 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/08 22:03:12 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "ast.h"
# include "minishell.h"
# include <sys/types.h>
# include <sys/wait.h>

/*execute_external.c*/
void	execute_external(char *cmd_path, char **args, char **env);
void	handle_external_command(char **args, char **env);

/*execute_node.c*/
int		execute_pipe_node(t_ast_node *node, t_minishell *shell);
int		execute_node(t_ast_node *node, t_minishell *shell);

/*external_utils.c*/
char	**get_paths_from_env(char **env);
char	*find_executable(char *cmd, char **paths);

/*heredoc.c*/
int		read_heredoc(char *delimiter);
void	process_heredocs(t_ast_node *node);

#endif