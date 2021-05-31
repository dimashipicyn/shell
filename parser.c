#include "libft.h"
#include "minishell.h"
#include "parser.h"

#define SINGLEQUOTE '\''
#define DOUBLEQUOTE '"'
#define BACKSLASH '\\'
#define DOLOR '$'

void	split_multitoken(t_vector *token, t_vector *tokens)
{
	t_vector	*split;
	t_vector	*temp;

	temp = 0;
	split = token->method->split(token, " ");
	if (!split)
		ft_eprintf("");
	if (has_next(split))
		temp = *(t_vector **)next(split);
	while (has_next(split))
	{
		tokens->method->push_back(tokens, &temp);
		temp = *(t_vector **)next(split);
	}
	if (split->size > 1)
		token->method->load(token, temp->mem, temp->size);
	delete(temp);
	delete(split);
}

t_vector	*get_token(t_vector *expression, t_vector *tokens, t_sh_data *sh_data)
{
	t_vector	*token;
	char		sym;
	char		prev_sym;

	token = new_vector(CHAR);
	if (!token)
		ft_eprintf("malloc token");
	prev_sym = 0;
	skip_delimiters(expression, " ");
	while (has_next(expression))
	{
		sym = *(char *)next(expression);
		if (ft_strchr(" ><|;", sym) && prev_sym != BACKSLASH)
		{
			previous(expression);
			break ;
		}
		if ((sym == SINGLEQUOTE || sym == DOUBLEQUOTE) && prev_sym != BACKSLASH)
			parse_quotes(expression, token, sh_data, sym);
		else if (sym == DOLOR && prev_sym != BACKSLASH)
		{
			parse_env_variable(expression, token, sh_data);
			split_multitoken(token, tokens);
		}
		else if (sym != BACKSLASH || prev_sym == BACKSLASH)
		{
			token->method->push_back(token, &sym);
			sym = 0;
		}
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
	ft_putendl_fd("argv", 1);
	while (ex.argv[i])
		ft_putendl_fd(ex.argv[i++], 1);
	ft_printf("pipe_out %d\n", ex.pipe_out);
	ft_printf("pipe_in %d\n", ex.pipe_in);
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
		parse_arguments(sh_data, expression);
		err_not = parse_redirects(sh_data, expression);
		parse_pipe(sh_data, expression);
		if (!err_not)
		{
			release_resources(sh_data);
			break ;
		}
//			print_params(sh_data);
		mediator(&(sh_data->exec_params), sh_data->envp);
		ft_printf("status: %d\n", sh_data->exec_params.status);
		release_resources(sh_data);
	}
}
