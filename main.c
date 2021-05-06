#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "term.h"
#include "history.h"
#include "readline.h"

#define PROMPT "\033[32mminishell:> \033[0m"
#define RIGHT_KEY "\E[C"
#define LEFT_KEY "\E[D"
#define UP_KEY "\E[A"
#define DOWN_KEY "\E[B"

void	print_newlines(int len)
{
	int	newlines;
	int	column;

	column = get_term_size();
	newlines = (len + 11) / column;
	while (newlines-- >= 0)
		ft_putendl_fd("", 1);
}

enum operator
{
	PIPE;
	FORWARD;
	BACKWARD;
	APPENDFOR;
	APPENDBACK;
}

typedef struct s_token
{
	t_vector		*tok;
	enum operator	op;
	int				fd;
}	t_token;

BOOLEAN is_operator(int character)
{
	if (character == '|' || character == '>' || character == '<')
	{
		return (TRUE);
	}
	return (FALSE);
}

void	lexer(t_vector *v)
{
	char	*ch;
	t_vector *tokens;
	t_vector *token;

	tokens = new_vector(PTR);
	token =  new_vector(CHAR);
	while (has_next(v))
	{
		ch = next(v);
		if (is_operator(*ch)) {
			ft_printf("\nop %c\n", *ch);
			break ;
		}
		token->method->push_back(token, ch);
	}
	ft_putendl_fd(token->mem, 1);
}

int	main(int argc, const char *argv[])
{
	t_history	*history;
	t_vector	*new_entry;

	init_term();
	history = new_history();
	history_load_in_file(history, "test.txt");
	set_input_mode();
	ft_putstr_fd(PROMPT, 1);
	while (1)
	{
		new_entry = new_vector(CHAR);
		history_push_front(history, new_entry);
		readline(history);
		print_newlines(new_entry->size);
		lexer(new_entry);
		ft_putstr_fd(PROMPT, 1);
	}
	history_save_to_file(history, "test.txt");
	reset_input_mode();
	return (0);
}
