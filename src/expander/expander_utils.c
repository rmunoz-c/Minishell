/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:43:44 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/12 21:32:08 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/minishell.h"

static char	*get_var_name(const char *str, size_t *i)
{
	size_t	start;

	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

static char	*expand_variable(const char *name, t_minishell *shell)
{
	size_t		j;
	size_t		len;

	if (ft_strncmp(name, "?", 2) == 0)
		return (ft_itoa(shell->exit_status));
	len = ft_strlen(name);
	j = 0;
	while (j < shell->env_count)
	{
		if (ft_strncmp(shell->envp[j].key, name, len) == 0
			&& shell->envp[j].key[len] == '\0')
			return (ft_strdup(shell->envp[j].value));
		j++;
	}
	return (ft_strdup(""));
}

static void	expand_from_dollar(const char *str, size_t *i,
	t_minishell *shell, char **result)
{
	char	*var;
	char	*tmp;

	var = get_var_name(str, i);
	tmp = expand_variable(var, shell);
	free(var);
	*result = ft_strjoinfree(*result, tmp);
	free(tmp);
}

static void	append_raw_segment(const char *str, size_t *i, char **result)
{
	size_t	start;
	char	*tmp;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	tmp = ft_substr(str, start, *i - start);
	*result = ft_strjoinfree(*result, tmp);
	free(tmp);
}

char	*expand_string(const char *str, t_minishell *shell)
{
	size_t	i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			expand_from_dollar(str, &i, shell, &result);
		}
		else
			append_raw_segment(str, &i, &result);
	}
	return (result);
}
