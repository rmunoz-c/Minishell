/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:35:09 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/10 18:35:44 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/token_list.h"
#include "../../includes/ast.h"
#include "../../libft/libft.h"

static size_t count_args(t_token_list *list, size_t start, size_t end)
{
	size_t i;
	size_t count;

	i = start;
	count = 0;
	while (i < end)
	{
		if (list->array[i].type != TOKEN_REDIRECT_IN
			&& list->array[i].type != TOKEN_REDIRECT_OUT
			&& list->array[i].type != TOKEN_PIPE
			&& list->array[i].type != TOKEN_EOF)
			count++;
		i++;
	}
	return count;
}

static void free_args_partial(char **args, size_t used)
{
	while (used > 0)
	{
		used--;
		free(args[used]);
	}
	free(args);
}

static char **allocate_args(t_token_list *list, size_t start, size_t end)
{
	size_t count;
	char **args;

	count = count_args(list, start, end);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return NULL;
	args[count] = NULL;
	return args;
}

static int fill_args(t_token_list *list, size_t start, size_t end, char **args)
{
	size_t i;
	size_t j;

	i = start;
	j = 0;
	while (i < end)
	{
		if (list->array[i].type != TOKEN_REDIRECT_IN
			&& list->array[i].type != TOKEN_REDIRECT_OUT
			&& list->array[i].type != TOKEN_PIPE
			&& list->array[i].type != TOKEN_EOF)
		{
			args[j] = ft_strdup(list->array[i].value);
			if (!args[j])
			{
				free_args_partial(args, j);
				return 0;
			}
			j++;
		}
		i++;
	}
	return 1;
}

static char **collect_args(t_token_list *list, size_t start, size_t end)
{
	char **args;
	int ok;

	args = allocate_args(list, start, end);
	if (!args)
		return NULL;
	ok = fill_args(list, start, end, args);
	if (!ok)
		return NULL;
	return args;
}