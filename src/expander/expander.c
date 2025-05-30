/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:50:24 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/29 21:20:42 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/token_list.h"
#include "../../libft/libft.h"
#include <stdlib.h>

char	*get_env_value(const char *name, t_envp *env, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (!ft_strcmp(env[i].key, (char *)name))
			return (ft_strdup(env[i].value));
		i++;
	}
	return (ft_strdup(""));
}

char	*expand_dollar(const char *str, size_t *i, t_minishell *shell)
{
	size_t	start;
	char	*var;
	char	*val;
	char	tmp[3];

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_status));
	}
	if (!ft_isalnum(str[*i]) && str[*i] != '_')
	{
		tmp[0] = '$';
		tmp[1] = str[*i];
		tmp[2] = '\0';
		if (str[*i])
			(*i)++;
		return (ft_strdup(tmp));
	}
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	if (!var)
		return (NULL);
	val = get_env_value(var, shell->envp, shell->env_count);
	free(var);
	return (val);
}

char	*expand_string(const char *str, t_minishell *shell)
{
	size_t	i;
	char	*res;
	char	*tmp;
	char	*exp;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			exp = expand_dollar(str, &i, shell);
			tmp = ft_strjoin(res, exp);
			(free(res), free(exp));
			res = tmp;
		}
		else
		{
			tmp = ft_substr(str, (i++, i - 1), 1);
			exp = ft_strjoin(res, tmp);
			(free(res), free(tmp));
			(res = exp);
		}
	}
	return (res);
}

void	expand_token_list(t_token_list *list, t_minishell *shell)
{
	size_t	i;
	char	*new;

	i = 0;
	while (i < list->size)
	{
		if (list->array[i].type == TOKEN_WORD
			&& list->array[i].in_single_quote == 0)
		{
			new = expand_string(list->array[i].value, shell);
			if (!new)
				return ;
			free(list->array[i].value);
			list->array[i].value = new;
		}
		i++;
	}
}

char	*expand_inside_string(const char *substr, t_minishell *shell)
{
	return (expand_string(substr, shell));
}
