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

static void	print_newlines(int len)
{
	int	newlines;
	int	column;

	column = get_term_size();
	newlines = (len + 11) / column;
	while (newlines-- >= 0)
		ft_putendl_fd("", 2);
}

static void	envp_copy(t_vector *envp_copy, const char **envp)
{
	char	*dup;

	while (*envp)
	{
		dup = ft_strdup(*envp);
		if (!dup)
			ft_eprintf("ft_strdup");
		envp_copy->method->push_back(envp_copy, &dup);
		envp++;
	}
}

static void	sh_init(t_sh_data *sh_data, const char **envp)
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
	envp_copy(envp_clone, envp);
	*sh_data = (t_sh_data){.history = history, .envp = envp_clone};
	sh_data->exec_params = (t_exec_params){.red_in = -1, .red_out = -1};
	set_input_mode();
}

int	main(int argc, const char *argv[], const char **envp)
{
	t_sh_data	sh_data;
	t_vector	*new_entry;

	sh_init(&sh_data, envp);
	ft_putstr_fd(PROMPT, 2);
	while (1)
	{
		new_entry = new_vector(CHAR);
		if (!new_entry)
			ft_eprintf("");
		history_push_front(sh_data.history, new_entry);
		readline(sh_data.history);
		print_newlines(new_entry->size);
		if (is_correct_syntax(new_entry))
		{
			parse_expression(&sh_data, new_entry);
		}
		ft_putstr_fd(PROMPT, 2);
	}
	return (0);
}
