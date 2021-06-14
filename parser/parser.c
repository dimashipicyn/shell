#include "minishell.h"
#include "parser.h"

void	split_multitoken(t_vector *token, t_vector *tokens)
{
	char		**split;
	int			it;
	int			last_elem;

	split = ft_split(token->mem, ' ');
	if (!split)
		return ;
	last_elem = ft_ptrlen((const void **)split) - 1;
	it = 0;
	while (it < last_elem)
	{
		tokens->method->push_back(tokens, split + it);
		it++;
	}
	if (last_elem >= 0)
	{
		token->method->load(token, split[last_elem], ft_strlen(split[last_elem]));
		free(split[last_elem]);
	}
	free(split);
}

t_vector	*get_token(t_vector *expression, t_vector *tokens, t_sh_data *sh_data)
{
	t_vector	*token;
	char		sym;
	char		prev_sym;

	token = new_vector(CHAR);
	if (!token)
		ft_eprintf("get token");
	prev_sym = 0;
	skip_delimiters(expression, " ");
	while (has_next(expression))
	{
		sym = *(char *)get_next(expression);
		if (ft_strchr(" ><|;", sym) && prev_sym != BACKSLASH)
			break ;
		next(expression);
		if ((sym == SINGLEQUOTE || sym == DOUBLEQUOTE) && prev_sym != BACKSLASH)
			parse_quotes(expression, token, sh_data, sym);
		else if (sym == DOLOR && prev_sym != BACKSLASH)
		{
			parse_env_variable(expression, token, sh_data);
			split_multitoken(token, tokens);
		}
		else if (sym != BACKSLASH || prev_sym == BACKSLASH)
			token->method->push_back(token, &sym);
		else
			prev_sym = sym;
	}
	return (token);
}

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

void	print_params(t_sh_data *sh_data)
{
	t_exec_params ex;
	int	i = 0;
	ex = sh_data->exec_params;
	while (ex.argv[i])
		ft_putendl_fd(ex.argv[i++], 1);
	ft_printf("pipe_out %d\n", ex.pipe_out);
	ft_printf("pipe_in %d\n", ex.pipe_in);
	ft_printf("red_in %d\n", ex.red_in);
	ft_printf("red_out %d\n", ex.red_out);
	ft_printf("argv %x\n", ex.argv);
}

void	release_resources(t_sh_data *sh_data)
{
	close(sh_data->exec_params.red_in);
	close(sh_data->exec_params.red_out);
	sh_data->exec_params.red_in = -1;
	sh_data->exec_params.red_out = -1;
	sh_data->exec_params.pipe_out = 0;
	sh_data->exec_params.pipe_in = 0;
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
//		print_params(sh_data);
//		ft_printf("err %d\n", err_not);
		if (!err_not || !sh_data->exec_params.argv[0])
		{
			release_resources(sh_data);
			break ;
		}
		errno = 0;
		mediator(&(sh_data->exec_params), sh_data->envp);
		release_resources(sh_data);
	}
}
