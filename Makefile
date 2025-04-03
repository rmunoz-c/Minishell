NAME := minishell

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS := -Wall -Werror -Wextra -g 
IFLAGS := -Iincludes -Ilibft
LFLAGS := -Llibft -lft -lreadline

SRC :=	src/expander/expander_build.c \
		src/expander/expander_utils.c \
		src/expander/expander.c \
		src/tokenizer/quote_handler.c \
		src/tokenizer/tokenizer_utils.c \
		src/tokenizer/tokenizer.c \
		src/free.c \
		src/test_tokenizer.c \
		src/token_list.c \

OBJ := $(SRC:.c=.o)

# Colores ANSI
BLUE := \033[34m
GREEN := \033[32m
YELLOW := \033[33m
CYAN := \033[36m
RESET := \033[0m

all: $(NAME)
	@printf "$(GREEN)\n✅ Compilación completa$(RESET)\n"

$(NAME): $(LIBFT) $(OBJ)
	@printf "$(CYAN)\r🔗 Enlazando: $(NAME)                     $(RESET)"
	@$(CC) $(OBJ) $(LIBFT) $(LFLAGS) -o $(NAME) $(CFLAGS)

%.o: %.c
	@printf "$(BLUE)\r⚙️  Compilando: $<                         $(RESET)"
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR)

clean:
	@printf "$(YELLOW)\r🧹 Limpiando objetos...                $(RESET)\n"
	@rm -f $(OBJ)
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

.DEFAULT_GOAL := all

.PHONY: all clean fclean re norm
