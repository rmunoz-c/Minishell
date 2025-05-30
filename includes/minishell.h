/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:08:26 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025/05/29 20:24:46 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
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
	TOKEN_REDIRECT_IN_DBL,
	TOKEN_REDIRECT_OUT_DBL,
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
	int						in_single_quote;
}							t_token;

typedef struct s_token_list	t_token_list;

typedef struct s_envp
{
	char					*key;
	char					*value;
}							t_envp;

typedef struct s_minishell
{
	t_envp					*envp;
	size_t					env_count;
	int						exit_status;
	t_token_list			*tokens;
}							t_minishell;

void						free_tokens(t_token_list *list);
void						free_envp(t_envp *envp, size_t count);
void						free_flat_env(char **env);

#endif
