#include "libft.h"
#include "minishell.h"

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

void	skip_delimiters(t_vector *vector, char *delim)
{
	char	ch;

	while (has_next(vector))
	{
		ch = *(char *)next(vector);
		if (!ft_strchr(delim, ch))
		{
			previous(vector);
			break ;
		}
	}
}

#define SINGLEQUOTE '\''
#define DOUBLEQUOTE '"'
#define BACKSLASH '\\'
#define DOLOR '$'

static t_vector	*get_token(t_vector *expression, t_vector *tokens, t_sh_data *sh_data)
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

BOOLEAN	reopen_file(char *filename, int flags, mode_t mode, int *fd)
{
	close(*fd);
	errno = 0;
	*fd = open(filename, flags, mode);
	if (*fd < 0)
		return (FALSE);
	return (TRUE);
}

BOOLEAN	open_file(t_sh_data *sh_data, char *op, char *filename)
{
	BOOLEAN	is_open;

	if (!ft_strcmp(op, ">>"))
		is_open = reopen_file(filename, O_APPEND | O_CREAT, 0644, &(sh_data->exec_params.red_out));
	else if (!ft_strcmp(op, ">"))
		is_open = reopen_file(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644, &(sh_data->exec_params.red_out));
	else if (!ft_strcmp(op, "<"))
		is_open = reopen_file(filename, O_RDONLY, 0644, &(sh_data->exec_params.red_in));
	else
	{
		ft_wprintf("unexpected token: %s", op);
		is_open = FALSE;
	}
	if (errno)
		ft_wprintf("can't open file %s", filename);
	errno = 0;
	return (is_open);
}

t_vector	*get_operator(t_vector *expression)
{
	char		sym;
	t_vector	*token;

	token = new_vector(CHAR);
	if (!token)
		ft_eprintf("malloc token");
	skip_delimiters(expression, " ");
	while (has_next(expression))
	{
		sym = *(char *)next(expression);
		if (!ft_strchr("><", sym))
		{
			previous(expression);
			break ;
		}
		token->method->push_back(token, &sym);
	}
	return (token);
}

BOOLEAN	parse_redirects(t_sh_data *sh_data, t_vector *expression)
{
	t_vector	*operator;
	t_vector	*operand;
	t_vector	*tokens;
	BOOLEAN		is_open;

	tokens = new_vector(PTR);
	if (!tokens)
		ft_eprintf("malloc tokens");
	while (has_next(expression))
	{
		operator = get_operator(expression);
		if (operator->size == 0 || !is_open)
		{
			delete(operator);
			break ;
		}
		operand = get_token(expression, tokens, sh_data);
		if (tokens->size != 0)
			ft_wprintf("ambiguous redirect");
		is_open = open_file(sh_data, operator->mem, operand->mem);
		delete(operator);
		delete(operand);
	}
	delete(tokens);
	return (is_open);
}

void	parse_arguments(t_sh_data *sh_data, t_vector *expression, t_vector *args)
{
	t_vector	*token;

	while (has_next(expression))
	{
		token = get_token(expression, args, sh_data);
		if (token->size == 0)
		{
			delete(token);
			break ;
		}
		args->method->push_back(args, &(token->mem));
	}
}

BOOLEAN	parse_expression(t_sh_data *sh_data, t_vector *expression)
{
	t_vector	*args;
	BOOLEAN		err_not;
	char		sym;

	expression->pos = 0;
	args = new_vector(PTR);
	if (!args)
		ft_eprintf("malloc args");
	while (has_next(expression))
	{
		sym = *(char *)get_next(expression);
		if (ft_strchr(";|", sym) || !err_not)
			break ;
		parse_arguments(sh_data, expression, args);
		err_not = parse_redirects(sh_data, expression);
	}
	if (sym == '|')
		sh_data->exec_params.pipe_out = 1;
	else
	{
		sh_data->exec_params.pipe_in = sh_data->exec_params.pipe_out;
		sh_data->exec_params.pipe_out = 0;
	}
	sh_data->exec_params.argv = args->mem;
	free(args);
	return (err_not);
}
	/*
	ft_printf("err_not %s\n", err_not ? "true" : "false");
	char	*t;
	ft_putendl_fd("args", 1);
	while (has_next(args))
	{
		t = *(char **)next(args);
		ft_putendl_fd(t, 1);
		free(t);
	}
	
	delete(args);
}
*/
