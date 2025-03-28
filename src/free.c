/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:52:30 by enogueir          #+#    #+#             */
/*   Updated: 2025/03/27 19:35:09 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_tokens(t_token *tokens, size_t count)
{
	size_t i;

	i = 0;
	while (i < count)
	{
		free(tokens[i].value);
		i++;
	}
	free(tokens);
}

