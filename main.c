#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "term.h"
#include "history.h"
#include "readline.h"
#include "minishell.h"

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

int	main(int argc, const char *argv[], const char **envp)
{
	t_history	*history;
	t_vector	*new_entry;
	t_vector	*envp_clone;

	init_term();
	history = new_history();
	history_load_in_file(history, "test.txt");
	envp_clone = new_vector(PTR);
	int i = 0;
	while (envp[i])
		i++;
	envp_clone->method->load(envp_clone, envp, i);
	set_input_mode();
	ft_putstr_fd(PROMPT, 1);
	while (1)
	{
		new_entry = new_vector(CHAR);
		history_push_front(history, new_entry);
		readline(history);
		print_newlines(new_entry->size);
		parse_expression(new_entry, envp_clone);
		ft_putstr_fd(PROMPT, 1);
	}
	history_save_to_file(history, "test.txt");
	reset_input_mode();
	return (0);
}
