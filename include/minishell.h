#ifndef MINISHELL_H
# define MINISHELL_H
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define PROMPT "\033[32mminishell:> \033[0m"

typedef struct s_history	t_history;

typedef struct s_exec_params
{
	int			pipe_in;
	int			pipe_out;
	int			red_in;
	int			red_out;
	int			fd_read;
	int			fd_write;
	int			save_fd_read;
	int			save_fd_write;
	int			status;
	char		**argv;
	t_vector	*envp;
}	t_exec_params;

typedef struct s_sh_data
{
	struct s_exec_params	exec_params;
	t_history				*history;
	t_vector				*envp;
}	t_sh_data;

void	parse_expression(t_sh_data *sh_data, t_vector *expression);
void	parse_env_variable(t_vector *expression,
			t_vector *token, t_sh_data *sh_data);
BOOLEAN	parse_quotes(t_vector *expression, t_vector *token,
			t_sh_data *sh_data, char quote);
BOOLEAN	is_correct_syntax(t_vector *expression);
void	mediator(t_exec_params *exec_params, t_vector *envp);
void	int_handler(int sig);
void	quit_handler(int sig);

#endif
