#ifndef MINISHELL_H
# define MINISHELL_H
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "object.h"
# include "vector.h"

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
    Vector(char_ptr_t)	*envp;
}	t_exec_params;

typedef struct s_sh_data
{
	struct s_exec_params	exec_params;
	t_history				*history;
    Vector(char_ptr_t)			*envp;
}	t_sh_data;

void	parse_expression(t_sh_data *sh_data, Vector(char) *expression);
void	parse_env_variable(Vector(char) *expression,
			Vector(char) *token, t_sh_data *sh_data);
BOOLEAN	parse_quotes(Vector(char) *expression, Vector(char) *token,
			t_sh_data *sh_data, char quote);
BOOLEAN	is_correct_syntax(Vector(char) *expression);
void	mediator(t_exec_params *exec_params, Vector(char) *envp);
void	int_handler(int sig);
void	quit_handler(int sig);
int		get_signal(void);
void	env_starter(Vector(char) *envp);

#endif
