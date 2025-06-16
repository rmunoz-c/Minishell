/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:05:33 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/16 20:20:58 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "ast.h"
# include "minishell.h"
# include <sys/types.h>
# include <sys/wait.h>

/*execute_builtin.c*/
int		execute_builtin(t_ast_node *node, t_minishell *shell);
int		is_builtin(const char *cmd);
int		is_exit_command(t_ast_node *ast);

/*execute_node.c*/
int		execute_node(t_ast_node *node, t_minishell *shell);

/*execute_pipe.c*/
pid_t	fork_left_pipe(t_ast_node *node, int fd[2], t_minishell *shell);
pid_t	fork_right_pipe(t_ast_node *node, int fd[2], t_minishell *shell);
int		execute_pipe_node(t_ast_node *node, t_minishell *shell);

/*execute_utils.c*/
char	**flatten_envp(t_envp *envp, size_t count);
void	free_flat_env(char **flat);
char	*resolve_cmd_path(t_ast_node *node, char **flat_env);

/*external_utils.c*/
char	**get_paths_from_env(char **env);
char	*find_executable(char *cmd, char **paths);

/*read_heredoc.c*/
char	*expand_line_heredoc(const char *line, t_minishell *shell);
int		read_heredoc(const char *delimiter, int *heredoc_fd,
			t_minishell *shell, int expand);
int		process_heredocs(t_ast_node *node, t_minishell *shell);

/*setup_redirectons.c*/
int		setup_redirections(t_ast_node *node);

#endif