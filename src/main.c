/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:18:59 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/28 18:02:44 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ast.h"
#include "../includes/execute.h"
#include "../includes/expander.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/token_list.h"
#include "../includes/tokenizer.h"
#include "../includes/builtins.h"
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern char **environ;


// void log_error_to_history(const char *error_message) {
//     FILE *history_file = fopen("history.txt", "a");
//     if (history_file == NULL) {
//         perror("Error abriendo el archivo de historial");
//         return;
//     }

//     // Añadir la línea de separación para un nuevo error
//     fprintf(history_file, "----------------------------\n");

//     // Registrar el mensaje de error
//     fprintf(history_file, "ERROR: %s\n", error_message);

//     // Registrar la fecha y hora del error
//     time_t rawtime;
//     struct tm *timeinfo;
//     char time_str[100];

//     time(&rawtime);
//     timeinfo = localtime(&rawtime);
//     strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);

//     fprintf(history_file, "Fecha y hora: %s\n", time_str);

//     fclose(history_file);
// }

// void handle_error(int sig) {
//     const char *error_message = NULL;

//     // Identificar el tipo de señal
//     switch (sig) {
//         case SIGSEGV:
//             error_message = "Segmentation fault (SIGSEGV) detected.";
//             break;
//         case SIGFPE:
//             error_message = "Floating point exception (SIGFPE) detected.";
//             break;
//         case SIGILL:
//             error_message = "Illegal instruction (SIGILL) detected.";
//             break;
//         case SIGABRT:
//             error_message = "Aborted (SIGABRT) detected.";
//             break;
//         default:
//             error_message = "Unknown error detected.";
//             break;
//     }

//     // Loggear el error y mostrarlo en la terminal
//     log_error_to_history(error_message);
//     fprintf(stderr, "ERROR: %s\n", error_message);

//     // Terminar el programa
//     exit(1);
// }

// void append_command_with_output_to_history(const char *command, const char *output) {
//     FILE *history_file = fopen("history.txt", "a");  // Abre el archivo en modo append
//     if (history_file == NULL) {
//         perror("Error abriendo el archivo de historial");
//         return;
//     }

//     fprintf(history_file, "Comando: %s\n", command);  // Escribe el comando en el archivo
//     fprintf(history_file, "Salida: %s\n\n", output);  // Escribe la salida del comando
//   	fprintf(history_file, "__________________________________________\n\n");
// 	fclose(history_file);
// }

// static	void add_separator_to_history() {
//     FILE *history_file = fopen("history.txt", "a");
//     if (history_file == NULL) {
//         perror("Error abriendo el archivo de historial");
//         return;
//     }
//     // Agregar la línea de separación al inicio de una nueva ejecución de minishell
//     fprintf(history_file, "----------------------------\n\n");
//     fclose(history_file);
// }

// void capture_and_save_output(const char *command, t_minishell *shell) {
//     int pipefd[2];
//     pid_t pid;
//     char output[1024];

//     if (pipe(pipefd) == -1) {
//         perror("Error al crear pipe");
//         return;
//     }

//     pid = fork();
//     if (pid == -1) {
//         perror("Error al crear proceso hijo");
//         return;
//     }

//     if (pid == 0) {
//         // Redirigir la salida estándar y la de error al pipe
//         close(pipefd[0]);
//         dup2(pipefd[1], STDOUT_FILENO);  // Redirigir stdout
//         dup2(pipefd[1], STDERR_FILENO);  // Redirigir stderr

//         // Ejecutar el comando real con execute_node
//         t_token_list list;
//         token_list_init(&list);
//         tokenize_input(command, &list);  // Tokenizar el comando
//         expand_token_list(&list);  // Expansión de la lista de tokens
//         t_ast_node *ast = parse_input(&list);  // Parsear el comando

//         if (ast) {
//             execute_node(ast, shell);  // Ejecutar el comando real con execute_node
//             ast_node_free(ast);
//         }

//         close(pipefd[1]);
//         exit(0);
//     } else {
//         // En el proceso padre
//         close(pipefd[1]);
//         ssize_t bytes_read = read(pipefd[0], output, sizeof(output) - 1);
//         if (bytes_read > 0) {
//             output[bytes_read] = '\0';  // Null-terminar la salida leída
//             // Guardar el comando y su salida en el archivo de historial
//             append_command_with_output_to_history(command, output);
//         }
//         close(pipefd[0]);

//         // Esperar a que el hijo termine
//         wait(NULL);
//     }
// }


static void	print_redirs(t_redir *redirs, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (redirs[i].type == TOKEN_REDIRECT_IN)
			printf("( < %s ) ", redirs[i].filename);
		else if (redirs[i].type == TOKEN_REDIRECT_OUT)
			printf("( > %s ) ", redirs[i].filename);
		else if (redirs[i].type == TOKEN_REDIRECT_OUT_DBL)
			printf("( >> %s ) ", redirs[i].filename);
		else if (redirs[i].type == TOKEN_REDIRECT_IN_DBL)
			printf("( << %s ) ", redirs[i].filename);
		i++;
	}
}

static void	print_node(t_ast_node *node)
{
	size_t	i;

	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
	{
		print_redirs(node->redirs, node->redir_count);
		printf("{ ");
		i = 0;
		while (node->args && node->args[i])
		{
			printf("%s ", node->args[i]);
			i++;
		}
		printf("}");
	}
	else if (node->type == NODE_PIPE)
	{
		print_node(node->left);
		printf("\n|\n");
		print_node(node->right);
	}
}

int main(int argc, char **argv, char **envp)
{
    char            *line;
    t_token_list    list;
    t_ast_node      *ast;
    t_minishell     shell;

    (void)argc;
    (void)argv;
    shell.envp = dup_envp_struct(envp, &shell.env_count);
	if(!shell.envp)
		exit(1);
	shell.exit_status = 0;
    while (1)
    {
        line = readline("PuenteCuatroShell > ");
        if (!line)
            break ;
        add_history(line);
        token_list_init(&list);
        tokenize_input(line, &list, &shell);
        expand_token_list(&list, &shell);
        ast = parse_input(&list);
       if (ast)
        {
            print_node(ast);
            printf("\n");
            process_heredocs(ast);
            execute_node(ast, &shell);
            ast_node_free(ast);
        }
        token_list_free(&list);
        free(line);
    }
	free_envp(shell.envp, shell.env_count);
    return (shell.exit_status);
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
