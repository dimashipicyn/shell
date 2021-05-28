CC = gcc
FLAGS = -Wall -Wextra -g -fsanitize=address# -Werror
VPATH := launcher:launcher/builtins 
SRCS = main.c term.c term2.c history1.c history2.c readline.c linenavigation.c ft_assert.c\
	   parser.c parse_env_var.c parse_quotes.c syntax_validator.c

SRCS += mediator.c launcher.c ft_errors.c ft_echo.c ft_pwd.c ft_cd.c
OBJ = $(SRCS:.c=.o)
NAME = minishell
LFT = libft.a

.PHONY: all clean fclean re

all: $(LFT) $(SRCS) $(NAME)

$(NAME): $(OBJ)
		gcc $(FLAGS) $(OBJ) $(LFT) -o $(NAME) -ltermcap -IDlib

$(LFT):
		make -C Dlib
		cp Dlib/$(LFT) .

.c.o: $(SRCS)
		$(CC) $(FLAGS) -c $< -IDlib

clean:
		@rm -rf $(OBJ)

fclean: clean
		@rm -rf $(NAME) $(LFT) $(LMLX)

re: fclean all
