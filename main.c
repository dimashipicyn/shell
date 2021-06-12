#include "minishell.h"

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
	t_vector	*entry;
	t_vector	*envp_clone;

	ft_setprogname("minishell");
	init_term();
	history = new_history();
	envp_clone = new_vector(PTR);
	entry = new_vector(CHAR);
	if (!envp_clone || !history || !entry)
		ft_eprintf("");
	history_load_in_file(history, "test.txt");
	history_push_front(history, entry);
	envp_copy(envp_clone, envp);
	*sh_data = (t_sh_data){.history = history, .envp = envp_clone};
	sh_data->exec_params = (t_exec_params){.red_in = -1, .red_out = -1};
}
int g_signal;

void	quit_handler(int sig)
{
	g_signal = sig;
	ft_putendl_fd("Quit 3", 2);
}

int	main(int argc, const char *argv[], const char **envp)
{
	t_sh_data	sh_data;
	t_vector	*entry;

	sh_init(&sh_data, envp);
	ft_putstr_fd(PROMPT, 2);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, quit_handler);
	while (1)
	{
		set_input_mode();
		entry = readline(sh_data.history);
		reset_input_mode();
		print_newlines(entry->size);
		if (entry->size > 0)
		{
			history_add(sh_data.history, entry);
			if (is_correct_syntax(entry))
				parse_expression(&sh_data, entry);
		}
		else
			delete(entry);
		//ft_fprintf(2, "sig %d\n", g_signal);
		//sh_data.exec_params.status = 128 + g_signal;
		ft_putstr_fd(PROMPT, 2);
	}
	return (0);
}
