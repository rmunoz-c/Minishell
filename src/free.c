/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:52:30 by enogueir          #+#    #+#             */
/*   Updated: 2025/03/13 19:53:30 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens(t_token **tokens, size_t token_count)
{
	size_t	i;

	if (!tokens)
		return ;
	i = 0;
	while (i < token_count)
	{
		if (tokens[i])
		{
			free(tokens[i]->value);
			free(tokens[i]);
		}
		i++;
	}
	free(tokens);
}
