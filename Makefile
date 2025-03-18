NAME= minishell

LIBFT_DIR= libft
LIBFT = $(LIBFT_DIR)/libft.a

CC= cc
CFLAGS= -Wall -Werror -Wextra -g

SRC=	src/expander.c \
		src/free.c \
		src/tokenizer_utils.c \
		src/tokenizer.c \
		src/test_tokenizer.c \

OBJ= $(SRC:.c=.o) 

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(MLX_LIBPATH)
	$(CC) $(OBJ) $(LIBFT) -o $(NAME) $(CFLAGS)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -o $@ $< -c

$(LIBFT):
	$(MAKE) -sC $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) fclean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm: 	
	@norminette include
	@norminette libft
	@norminette $(SRC)

.DEFAULT_GOAL: all

.PHONY: all clean fclean re
