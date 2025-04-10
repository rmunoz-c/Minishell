/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:32:47 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/10 17:32:56 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ast.h"
# include "token_list.h"

t_ast_node *parse_input(t_token_list *list);
t_ast_node *parse_pipeline(t_token_list *list, size_t start, size_t end);
t_ast_node *parse_command(t_token_list *list, size_t start, size_t end);

#endif