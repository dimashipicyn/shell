CC = gcc
FLAGS = -Wall -Wextra -g -fsanitize=address# -Werror

SRCS = main.c term.c term2.c history1.c history2.c readline.c linenavigation.c
OBJ = $(SRCS:.c=.o)
NAME = minishell
LFT = libft.a

.PHONY: all clean fclean re

all: $(LFT) $(SRCS) $(NAME)

$(NAME): $(OBJ)
		gcc $(FLAGS) $(OBJ) $(LFT) -o $(NAME) -ltermcap -Ilft

$(LFT):
		make -C lft
		cp lft/$(LFT) .

.c.o: $(SRCS)
		$(CC) $(FLAGS) -c $< -Ilft

clean:
		@rm -rf $(OBJ)

fclean: clean
		@rm -rf $(NAME) $(LFT) $(LMLX)

re: fclean all
