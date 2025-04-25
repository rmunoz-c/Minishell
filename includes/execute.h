/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:05:33 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/24 18:10:56 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include "minishell.h"
#include "ast.h"
#include <sys/types.h>
#include <sys/wait.h>

/*execute_node.c*/
int	execute_node(t_ast_node *node, t_minishell *shell);

/*heredoc.c*/
int	read_heredoc(char *delimiter);

#endif