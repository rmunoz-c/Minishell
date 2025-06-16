# Nombre del ejecutable
NAME := minishell

# Rutas de librerías
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

# Compilador y flags
CC = cc
CFLAGS := -Wall -Werror -Wextra -g -MMD -MP
IFLAGS := -Iincludes -Ilibft
LFLAGS := -Llibft -lft -lreadline

# Rutas de fuentes y objetos
SRC :=	src/ast/ast.c \
		src/builtins/builtin_basic.c \
		src/builtins/builtin_envmod.c \
		src/builtins/builtin_exit.c \
		src/builtins/builtin_export_utils.c \
		src/builtins/builtin_export.c \
		src/builtins/builtin_unset.c \
		src/env/env_utils.c \
		src/exec/execute_builtin.c \
		src/exec/execute_node.c \
		src/exec/execute_pipe.c \
		src/exec/execute_utils.c \
		src/exec/external_utils.c \
		src/exec/read_heredoc.c \
		src/exec/setup_redirections.c \
		src/expander/expander_build.c \
		src/expander/expander_utils.c \
		src/expander/expander.c \
		src/lexer/token_list.c \
		src/lexer/tokenizer_assign.c \
		src/lexer/tokenizer_utils.c \
		src/lexer/tokenizer.c \
		src/parser/parse_command.c \
		src/parser/parse_input.c \
		src/parser/parse_pipeline.c \
		src/parser/validate_syntax.c \
		src/signals/signal.c \
		src/free.c \
		src/initialize_shell.c \
		src/main.c \
		src/shell_loop.c \

BUILD_DIR := build
OBJ := $(SRC:.c=.o)
OBJ := $(addprefix $(BUILD_DIR)/, $(OBJ))
DEP := $(OBJ:.o=.d)

# Colores ANSI
BLUE := \033[34m
GREEN := \033[32m
YELLOW := \033[33m
CYAN := \033[36m
RESET := \033[0m

.DEFAULT_GOAL := all

all: $(NAME)
	@printf "$(GREEN)\n✅ Compilación completa$(RESET)\n"

$(NAME): $(OBJ) $(LIBFT)
	@printf "$(CYAN)\r🔗 Enlazando: $(NAME)                     $(RESET)\n"
	@$(CC) $(OBJ) $(LIBFT) $(LFLAGS) -o $(NAME) $(CFLAGS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(BLUE)\r⚙️  Compilando: $<                         $(RESET)"
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR)

run: $(NAME)
	@./$(NAME)

clean:
	@printf "$(YELLOW)\r🧹 Limpiando objetos...                $(RESET)\n"
	@rm -rf $(BUILD_DIR)
	@printf "$(GREEN)\r🧹  Limpiando LIBFT.                    $(RESET)\n"
	@$(MAKE) -sC $(LIBFT_DIR) fclean

fclean: clean
	@printf "$(YELLOW)\r🗑️  Borrando ejecutable...              $(RESET)\n"
	@rm -f $(NAME)
	@printf "$(GREEN)\r✅  Limpieza completa.                  $(RESET)\n"

re: fclean all

norm: 	
	@printf "$(YELLOW)\n🔍 Revisando con norminette...$(RESET)\n"
	@norminette includes
	@norminette libft
	@norminette $(SRC)

# Incluir dependencias automáticas
-include $(DEP)


.PHONY: all clean fclean re norm run test
