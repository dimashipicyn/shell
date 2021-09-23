#include "minishell.h"
#include "parser.h"

void	parse_pipe(t_sh_data *sh_data, Iterator(char) *iterExpr)
{
	char		sym;

	sym = 0;
	sh_data->exec_params.pipe_in = sh_data->exec_params.pipe_out;
	sh_data->exec_params.pipe_out = FALSE;
	if (m_has_next(iterExpr)) {
	    sym = m_next(iterExpr);
	    if (sym == '|')
	        sh_data->exec_params.pipe_out = TRUE;
	    m_prev(iterExpr);
	}
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

void print(t_sh_data *sh_data)
{
    printf("pipe in %d\n", sh_data->exec_params.pipe_in);
    printf("pipe out %d\n", sh_data->exec_params.pipe_out);
    printf("red in %d\n", sh_data->exec_params.red_in);
    printf("red out %d\n", sh_data->exec_params.red_out);
    for (int i = 0; sh_data->exec_params.argv[i] != 0; i++)
        printf("argv [%d] %s\n", i, sh_data->exec_params.argv[i]);
}

bool    is_end(Iterator(char) *iterExpr)
{
    char ch;

    if (m_has_next(iterExpr)) {
        ch = m_get(iterExpr);
        if (ch == ';' || ch == '|') {
            m_next(iterExpr);
            return true;
        }
        return false;
    }
    return true;
}

void	parse_expression(t_sh_data *sh_data, Vector(char) *expression)
{
	BOOLEAN		    err_not;
    Iterator(char)  *iterExpr;

	err_not = TRUE;
	iterExpr = $(Iterator(char), expression);
	while (m_has_next(iterExpr))
	{
	    while (m_has_next(iterExpr)) {
	        errno = 0;
	        parse_arguments(sh_data, iterExpr);
	        err_not = parse_redirects(sh_data, iterExpr);
	        parse_pipe(sh_data, iterExpr);
	        //print(sh_data); // debug
	        if (is_end(iterExpr))
	            break;
	    }
		if (!err_not)
		{
			sh_data->exec_params.pipe_out = 0;
			sh_data->exec_params.pipe_in = 0;
			release_resources(sh_data);
			break ;
		}
		mediator(&(sh_data->exec_params), sh_data->envp);
		release_resources(sh_data);
	}
}
