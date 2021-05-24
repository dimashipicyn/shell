#ifndef MINISHELL_H
# define MINISHELL_H
# include "history.h"

typedef struct	s_exec_params
{
	int			pipe_in;
	int			pipe_out;
	int			red_in;
	int 		red_out;
	int			fd_read;
	int 		fd_write;
	int			save_fd_read;
	int			save_fd_write;
	int			status;
	char 		**argv;
	t_vector	*envp;
}	t_exec_params;

typedef struct	s_sh_data
{
	struct s_exec_params	exec_params;
	t_history				*history;
	t_vector				*envp;
}	t_sh_data;

BOOLEAN	parse_expression(t_sh_data *sh_data, t_vector *expression);
void	parse_env_variable(t_vector *expression, t_vector *token, t_sh_data *sh_data);
BOOLEAN	parse_quotes(t_vector *expression, t_vector *token, t_sh_data *sh_data, char quote);

#endif
