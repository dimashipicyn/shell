#include "minishell.h"
#include "parser.h"

void	parse_pipe(t_sh_data *sh_data, t_vector *expression)
{
	char		sym;

	sym = 0;
	if (has_next(expression))
		sym = *(char *)next(expression);
	sh_data->exec_params.pipe_in = sh_data->exec_params.pipe_out;
	if (sym == '|')
		sh_data->exec_params.pipe_out = TRUE;
	else
		sh_data->exec_params.pipe_out = FALSE;
}

void	release_resources(t_sh_data *sh_data)
{
	close(sh_data->exec_params.red_in);
	close(sh_data->exec_params.red_out);
	sh_data->exec_params.red_in = -1;
	sh_data->exec_params.red_out = -1;
	ft_free_array_ptr((void **)sh_data->exec_params.argv);
	sh_data->exec_params.argv = 0;
}

void	parse_expression(t_sh_data *sh_data, t_vector *expression)
{
	BOOLEAN		err_not;

	expression->pos = 0;
	err_not = TRUE;
	while (has_next(expression))
	{
		errno = 0;
		parse_arguments(sh_data, expression);
		err_not = parse_redirects(sh_data, expression);
		parse_pipe(sh_data, expression);
		if (!err_not || !sh_data->exec_params.argv[0])
		{
			sh_data->exec_params.pipe_out = 0;
			sh_data->exec_params.pipe_in = 0;
			release_resources(sh_data);
			break ;
		}
		errno = 0;
		mediator(&(sh_data->exec_params), sh_data->envp);
		release_resources(sh_data);
	}
}
