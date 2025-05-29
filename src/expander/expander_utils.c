/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:28:45 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/28 18:05:27 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/minishell.h"
#include "../../libft/libft.h"

char	*expand_exit_status(t_minishell *shell)
{
	return (ft_itoa(shell->exit_status));
}

char	*expand_variable(const char *var)
{
	char	*value;

	if (!var)
		return (NULL);
	value = getenv(var);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

int	append_char_to_result(char c, char **result)
{
	char	buff[2];
	char	*temp;

	buff[0] = c;
	buff[1] = '\0';
	temp = ft_strjoin(*result, buff);
	if (!temp)
		return (0);
	free(*result);
	*result = temp;
	return (1);
}

int	process_expansion(const char *str, size_t *pos, char **res,
						t_minishell *shell)
{
	if (str[*pos] == '$' && str[*pos + 1])
		return (expand_and_join(str, pos, res, shell));
	if (!append_char_to_result(str[*pos], res))
		return (0);
	(*pos)++;
	return (1);
}

int	expand_and_join(const char *str, size_t *pos, char **result,
					t_minishell *shell)
{
	char	*temp;
	char	*expanded;

	expanded = expand_dollar(str, pos, shell);
	if (!expanded)
		return (0);
	temp = ft_strjoin(*result, expanded);
	free(expanded);
	if (!temp)
		return (0);
	free(*result);
	*result = temp;
	return (1);
}
