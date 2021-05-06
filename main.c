#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "vector.h"
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

void	lexer(t_vector *v)
{
	char	*ch;
	t_vector *token;
	t_vector *tokens;

	token = new_vector(CHAR);
	tokens = new_vector(PTR);
//	while (has_next(v)) {
	while (has_next(v))
	{
		ch = next(v);
		ft_printf("\nnext %c", *ch);
		if (*ch == ' ')
			break;
		token->method->push_back(token, &ch);
	}
//	tokens->method->push_back(tokens, &token);
//	}
	/*
	while (has_next(tokens))
	{
		token = next(tokens);
		ft_printf("%s\n", token->mem);
	}
	*/
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
