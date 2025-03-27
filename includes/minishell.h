/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:08:26 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025/03/27 19:39:08 by enogueir         ###   ########.fr       */
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
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	size_t			length;
}					t_token;

extern int			g_last_exit_status;

void free_tokens(t_token *tokens, size_t count);

#endif
