#include "minishell.h"
#include "history.h"
#include "termc.h"
#include "readline.h"
#define T Vector(char)
#include "vector.h"

static void	envp_copy(Vector(char_ptr_t) *envp_copy, const char **envp)
{
	char	*dup;

	while (*envp)
	{
		dup = ft_strdup(*envp);
		if (!dup)
			ft_eprintf("ft_strdup");
		m_push_back(envp_copy, dup);
		envp++;
	}
}

static void	sh_init(t_sh_data *sh_data, const char **envp)
{
	t_history	                *history;
    Vector(char)                *entry;
    Vector(char_ptr_t)	        *envp_clone;
	BOOLEAN		                is_term;

	is_term = init_term();
	setprogname("minishell");
	history = new_history();
	envp_clone = new(Vector(char_ptr_t));
	entry = new(Vector(char));
	if (!envp_clone || !history || !entry)
		ft_eprintf("");
	history_load_in_file(history, HISTORY_PATH);
	history_push_front(history, entry);
	envp_copy(envp_clone, envp);
	*sh_data = (t_sh_data){.history = history, .envp = envp_clone};
	sh_data->exec_params = (t_exec_params){.red_in = -1, .red_out = -1};
	if (!is_term)
	{
	//	interpret_stdin(sh_data);
		exit(0);
	}
	//env_starter(envp_clone);
}

static void	minishell_usage(int ac, const char **av)
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
	t_sh_data	    sh_data;
    Vector(char)    *entry;

	sh_init(&sh_data, envp);
	minishell_usage(argc, argv);
	ft_putstr_fd(PROMPT, 2);
	//signal(SIGINT, int_handler);
	//signal(SIGQUIT, quit_handler);

	while (1)
	{
		set_input_mode();
		entry = readline(sh_data.history);
		reset_input_mode();
		ft_putendl_fd("", 2);
		if (entry->size > 0)
		{
			history_add(sh_data.history, entry);
			//if (is_correct_syntax(entry))
			//	parse_expression(&sh_data, entry);
		}
		else
			delete(entry);
		ft_putstr_fd(PROMPT, 2);
	}
	return (0);
}
