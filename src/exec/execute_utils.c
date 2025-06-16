/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:55:35 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/12 21:30:03 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/minishell.h"
#include "../../includes/execute.h"

char	**flatten_envp(t_envp *envp, size_t count)
{
	char	**flat;
	size_t	i;
	size_t	len;

	flat = malloc(sizeof(char *) * (count + 1));
	if (!flat)
		return (NULL);
	i = 0;
	while (i < count)
	{
		len = strlen(envp[i].key) + strlen(envp[i].value) + 2;
		flat[i] = malloc(len);
		if (!flat[i])
			return (NULL);
		strcpy(flat[i], envp[i].key);
		strcat(flat[i], "=");
		strcat(flat[i], envp[i].value);
		i++;
	}
	flat[i] = NULL;
	return (flat);
}

void	free_flat_env(char **flat)
{
	size_t	i;

	i = 0;
	while (flat && flat[i])
		free(flat[i++]);
	free(flat);
}
