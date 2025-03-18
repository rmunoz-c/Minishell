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

<<<<<<< HEAD
#include "../includes/minishell.h"

int	g_last_exit_status = 0;
=======
#include "../includes/expander.h"
>>>>>>> 789d6fb5db893a411c49f0c5dbe4b7f7a84649b0

char	*expand_variable(const char *var)
{
	char	*value;
	char	*expanded;

<<<<<<< HEAD
	if (!var || *var == '\0')
		return (NULL);
	if (*var == '$')
		var++;
=======
>>>>>>> 789d6fb5db893a411c49f0c5dbe4b7f7a84649b0
	value = getenv(var);
	if (!value)
	{
		expanded = malloc(1);
		if (!expanded)
			return (NULL);
		expanded[0] = '\0';
		return (expanded);
	}
<<<<<<< HEAD
	expanded = ft_strdup(value);
=======
	expanded = strdup(value);
>>>>>>> 789d6fb5db893a411c49f0c5dbe4b7f7a84649b0
	return (expanded);
}

char	*expand_exit_status(void)
{
	return (ft_itoa(g_last_exit_status));
}
