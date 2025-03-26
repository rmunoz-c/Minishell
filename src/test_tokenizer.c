# include "../includes/tokenizer.h"
# include <readline/readline.h>
# include <readline/history.h>

int	main(void)
{
	t_token	**tokens;
	size_t	token_count;
	size_t	i;
	char	*input;

	// input = "echo hola $USER que tal estas? \"$HOME\" d $PWD";
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
			printf("Token [%s], Tipo: %d, Longitud: %zu\n",
				tokens[i]->value, tokens[i]->type, tokens[i]->length);
			i++;
		}
		free_tokens(tokens, token_count);
		free(input);
	}

	return (0);
}
