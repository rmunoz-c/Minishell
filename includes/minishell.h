/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:08:26 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025/04/03 18:12:53 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <ctype.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_SPACE,
	TOKEN_ERROR,
	TOKEN_EOF,
	TOKEN_ENV_VAR
}							t_token_type;

typedef struct s_token
{
	t_token_type			type;
	char					*value;
	size_t					length;
}							t_token;

typedef struct s_token_list	t_token_list;

typedef struct s_minishell
{
	char					**envp;
	t_token_list			*tokens;
}							t_minishell;

extern int					g_exit_status;

void						free_tokens(t_token_list *list);

#endif
