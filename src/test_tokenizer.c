/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:18:59 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/03 18:49:26 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/minishell.h"
#include "../includes/token_list.h"
#include "../includes/tokenizer.h"
#include "../includes/expander.h"
#include "../libft/libft.h"

int main(void)
{
	t_token_list list;
	char         *input;
	size_t       i;

	while (1)
	{
		input = readline("PuenteCuatroShell > ");
		if (!input)
			break;
		add_history(input);
		token_list_init(&list);
		tokenize_input(input, &list);
		expand_token_list(&list);
		i = 0;
		while (i < list.size && list.array[i].type != TOKEN_EOF)
		{
			printf("Token [%s], Tipo: %d, Longitud: %zu\n",
				list.array[i].value,
				list.array[i].type,
				list.array[i].length);
			i++;
		}
		token_list_free(&list);
		free(input);
	}
	return (0);
}


/*(int	main(void)
{
	t_token	*tokens;
	size_t	token_count;
	size_t	i;
	char	*input;

	while (1)
	{
		input = readline("PuenteCuatroShell > ");
		add_history(input);
		tokens = tokenize(input, &token_count);
		if (!tokens)
			return (printf("Error en el tokenizador\n"), 1);
		i = 0;
		while (i < token_count && tokens[i]->type != TOKEN_EOF)
		{
			printf("Token [%s], Tipo: %d, Longitud: %zu\n", tokens[i]->value,
				tokens[i]->type, tokens[i]->length);
			i++;
		}
		free_tokens(tokens, token_count);
		free(input);
	}
	return (0);
}*/

// input = "echo hola $USER que tal estas? "$HOME" d $PWD";
