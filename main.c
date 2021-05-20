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

void	sh_init(t_sh_data *sh_data, const char **envp)
{
	t_history	*history;
	t_vector	*envp_clone;

	ft_setprogname("minishell");
	init_term();
	history = new_history();
	envp_clone = new_vector(PTR);
	if (!envp_clone || !history)
		ft_eprintf("");
	history_load_in_file(history, "test.txt");
	envp_clone->method->load(envp_clone, envp, ft_ptrlen((const void**)envp));
	*sh_data = (t_sh_data){.history = history, .envp = envp_clone};
	set_input_mode();
}

int	main(int argc, const char *argv[], const char **envp)
{
	t_sh_data	sh_data;
	t_vector	*new_entry;

	sh_init(&sh_data, envp);
	ft_putstr_fd(PROMPT, 1);
	while (1)
	{
		new_entry = new_vector(CHAR);
		if (!new_entry)
			ft_eprintf("");
		history_push_front(sh_data.history, new_entry);
		readline(sh_data.history);
		print_newlines(new_entry->size);
		parse_expression(&sh_data, new_entry);
		ft_putstr_fd(PROMPT, 1);
	}
	return (0);
}
