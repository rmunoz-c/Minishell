/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:50:24 by enogueir          #+#    #+#             */
/*   Updated: 2025/03/13 19:51:05 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_last_exit_status = 0;

char	*expand_variable(const char *var)
{
	char	*value;
	char	*expanded;

	if (!var || *var == '\0')
		return (NULL);
	if (*var == '$')
		var++;
	value = getenv(var);
	if (!value)
	{
		expanded = malloc(1);
		if (!expanded)
			return (NULL);
		expanded[0] = '\0';
		return (expanded);
	}
	expanded = ft_strdup(value);
	return (expanded);
}

char	*expand_exit_status(void)
{
	return (ft_itoa(g_last_exit_status));
}
