#include "minishell.h"
#include "history.h"
#include "termc.h"
#include "readline.h"

/***
 * Копирует массив с енв в вектор
 * @param envp_copy
 * @param envp
 */

static Vector(char_ptr_t)	*envp_copy(const char **envp)
{
    char	            *dup;
    Vector(char_ptr_t)  *envp_copy;

    envp_copy = new(Vector(char_ptr_t));
    if (!envp_copy)
        ft_eprintf("");
	while (*envp)
	{
		dup = strdup(*envp);
		if (!dup)
			ft_eprintf("ft_strdup");
		m_push_back(envp_copy, dup);
		envp++;
	}
    return envp_copy;
}

t_sh_data *constructor_t_sh_data(t_sh_data *sh_data, const char **envp)
{
    t_history	                *history;
    Vector(char_ptr_t)	        *envp_clone;

    history = new(t_history);
    envp_clone = envp_copy(envp);
	if (!history)
		ft_eprintf("");
	*sh_data = (t_sh_data){.history = history, .envp = envp_clone};
	sh_data->exec_params = (t_exec_params){.red_in = -1, .red_out = -1};
	return sh_data;
}

static void	minishell_usage(int ac, const char **av)
{
	if (ac > 1)
	{
		if (!strcmp(av[1], "--help"))
		{
			printf("Minishell Zip-zipulya. Version 1.0\n");
			printf("Usage:\t minishell [option]\n");
			printf("Options:\n");
			printf("\t--help\n");
			exit(0);
		}
	}
}

int	main(int argc, const char *argv[], const char **envp)
{
	t_sh_data	    *sh_data;
    Vector(char)    *entry;
    BOOLEAN		    is_term;

    minishell_usage(argc, argv);
    setprogname("minishell");
	sh_data = $(t_sh_data, envp);
	is_term = init_term();
	// если устройство не терминал, считываем команду с инпута
	if (!is_term)
	{
	    interpret_stdin(sh_data);
	    exit(0);
	}
	env_starter(sh_data->envp);
	ft_putstr_fd(PROMPT, 2);
	signal(SIGINT, int_handler);
	signal(SIGQUIT, quit_handler);

	while (1)
	{
		set_input_mode();
		entry = readline(sh_data->history);
		reset_input_mode();
		ft_putendl_fd("", 2);
		if (entry->size > 0)
		{
			history_add(sh_data->history, entry);
			if (is_correct_syntax(entry))
				parse_expression(sh_data, entry);
		}
		else
			delete(entry);
		ft_putstr_fd(PROMPT, 2);
	}
	return (0);
}
