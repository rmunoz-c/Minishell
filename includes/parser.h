/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:32:47 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/12 21:13:14 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ast.h"
# include "token_list.h"

/*parse_command.c*/
t_ast_node	*parse_command(t_token_list *list, size_t start, size_t end);

/*parse_input.c*/
t_ast_node	*parse_input(t_token_list *list);

/*parse_pipeline.c*/
t_ast_node	*parse_pipeline(t_token_list *list, size_t start, size_t end);

/*validate_syntax.c*/
int			validate_token_syntax(t_token_list *list);

#endif