CC = gcc
FLAGS = -Wall -Wextra -MMD# -g -fsanitize=address# -Werror
VPATH := launcher:launcher/builtins:Dlib 
SRCS = main.c term.c term2.c history1.c history2.c readline.c linenavigation.c\
	   parser.c parse_env_var.c parse_quotes.c syntax_validator.c\
	   parse_argument.c parse_redirect.c

SRCS += mediator.c launcher.c ft_errors.c ft_echo.c ft_pwd.c ft_cd.c ft_export.c\
		ft_env.c ft_unset.c

INC = minishell.h parser.h history.h readline.h linenavigation.h term.h

OBJ = $(SRCS:.c=.o)
DEPENDS = ${SRCS:.c=.d}
NAME = minishell
LFT = libft.a

.PHONY: all clean fclean re lib gitadd

all: lib $(SRCS) $(NAME)

$(NAME): $(OBJ)
		gcc $(FLAGS) $(OBJ) $(LFT) -o $(NAME) -ltermcap -IDlib

lib:
		make -C Dlib
		cp Dlib/$(LFT) .

.c.o: $(SRCS)
		$(CC) $(FLAGS) -c $< -IDlib

clean:
		@rm -rf $(OBJ)

fclean: clean
		@rm -rf $(NAME) $(LFT) $(LMLX)

re: fclean all

gitadd: $(SRCS) $(INC)
	git add $^
	git add Makefile

-include ${DEPENDS}
