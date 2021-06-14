#include "minishell.h"
#include "history.h"
#include "termc.h"
#include "readline.h"

static void	print_newlines(int len)
{
	int	newlines;
	int	column;

	column = get_term_size();
	newlines = (len + 11) / column;
	while (newlines-- > 0)
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
	BOOLEAN		is_term;

	is_term = init_term();
	ft_setprogname("minishell");
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
	if (!is_term)
	{
		t_vector *entry = new_vector(CHAR);
		char buf[1001];
		ft_bzero(buf, 1001);
		read(0, buf, 1000);
		int size = ft_strlen(buf);
		if (size > 0)
			size -= 1;
		entry->method->load(entry, buf, size);
		if (entry->size > 0)
		{
			if (is_correct_syntax(entry))
				parse_expression(sh_data, entry);
		}
		delete(entry);
		exit(0);
	}
}
int g_signal;

void	quit_handler(int sig)
{
	g_signal = sig;
	ft_putendl_fd("Quit 3", 2);
}

void	int_handler(int sig)
{
	g_signal = sig;
	ft_putendl_fd("", 2);
}

void	minishell_usage(int ac, const char **av)
{
	if (ac > 1)
	{
		if (!ft_strcmp(av[1], "--help"))
		{
			ft_printf("Minishell Zip-zipulya. Version 1.0\n");
			ft_printf("Usage:\t minishell [option]\n");
			ft_printf("Options:\n");
			ft_printf("\t--help\n");
			exit(0);
		}
	}
}

int	main(int argc, const char *argv[], const char **envp)
{
	t_sh_data	sh_data;
	t_vector	*entry;

	sh_init(&sh_data, envp);
	minishell_usage(argc, argv);
	ft_putstr_fd(PROMPT, 2);
	signal(SIGINT, int_handler);
	signal(SIGQUIT, quit_handler);
	while (1)
	{
		set_input_mode();
		entry = readline(sh_data.history);
		reset_input_mode();
		ft_putendl_fd("", 2);
		if (entry->size > 0)
		{
			history_add(sh_data.history, entry);
			if (is_correct_syntax(entry))
				parse_expression(&sh_data, entry);
		}
		else
			delete(entry);
		ft_putstr_fd(PROMPT, 2);
	}
	return (0);
}
