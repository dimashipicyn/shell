CC = gcc
FLAGS = -Wall -Wextra -MMD# -g -fsanitize=address# -Werror
VPATH := launcher:history:builtins:parser:readline:term:signal:include:Dlib:miniobjectc
SRCS = main.c term.c term2.c history1.c history2.c readline.c linenavigation.c\
#	   syntax_validator.c#\
	   #parser.c parse_env_var.c parse_quotes.c
	   #parse_argument.c parse_redirect.c interpret_stdin.c signal.c get_token.c
#SRCS += mediator.c launcher.c ft_echo.c ft_pwd.c ft_cd.c ft_export.c\
		ft_env.c ft_unset.c pipeworks.c redirects.c filepath.c envstarter.c

INC = minishell.h parser.h history.h readline.h linenavigation.h termc.h inc.h utils.h structs.h\
		pipe_redirects.h

OBJ = $(SRCS:.c=.o)
DEPENDS = ${SRCS:.c=.d}
NAME = minishell
LFT = libft.a

.PHONY: all clean fclean re lib gitadd

all: lib $(SRCS) $(NAME)
	./minishell

$(NAME): $(OBJ)
		gcc $(FLAGS) $(OBJ) $(LFT) libminiooc.a -o $(NAME) -ltermcap

lib:
		make -C Dlib
		cp Dlib/$(LFT) .
		make -C miniobjectc
		cp miniobjectc/libminiooc.a .

.c.o: $(SRCS)
		$(CC) $(FLAGS) -c $< -I./include -I./Dlib -I./miniobjectc/include

clean:
		@rm -rf $(OBJ) $(DEPENDS)

fclean: clean
		@rm -rf $(NAME) $(LFT)

re: fclean all

gitadd: $(SRCS) $(INC)
	git add $^
	git add Makefile

norm: $(SRCS) $(INC)
	norminette $^

-include ${DEPENDS}
