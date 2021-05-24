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
/*
int		open_file(t_vector *expression, t_sh_data * sh_data)
{
	t_vector	*token;
	t_vector	*tokens;
	int			fd;
	char		ch;

	ch = 0;
	if (has_next(expression))
	{
		ch = *(char *)next(expression);
		if (ch != '>')
			previous(expression);
	}
	tokens = new_vector(PTR);
	if (!tokens)
		ft_eprintf("");
	token = get_token(expression, tokens, sh_data);
	if (ch == '>')
		fd = open(token->mem, O_APPEND | O_CREAT, 0777);
	else
		fd = open(token->mem, O_RDWR | O_CREAT, 0777);
	if (fd < 0)
		ft_wprintf("can't open file %s", token->mem);
	return (fd);
}
*/
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

void	parse_redirects(t_sh_data *sh_data, t_vector *expression, t_vector *redirects)
{
	t_vector	*operator;
	t_vector	*operand;
	t_vector	*tokens;

	tokens = new_vector(PTR);
	if (!tokens)
		ft_eprintf("malloc tokens");
	while (has_next(expression))
	{
		operator = get_operator(expression);
		if (operator->size == 0)
		{
			delete(operator);
			break ;
		}
		operand = get_token(expression, tokens, sh_data);
		if (tokens->size != 0)
			ft_wprintf("ambiguous redirect");
		redirects->method->push_back(redirects, &operator);
		redirects->method->push_back(redirects, &operand);
	}
	delete(tokens);
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
		args->method->push_back(args, &token);
	}
}

void	parse_expression(t_sh_data *sh_data, t_vector *expression)
{
	t_vector	*args;
	t_vector	*redirects;

	expression->pos = 0;
	args = new_vector(PTR);
	redirects = new_vector(PTR);
	if (!args || !redirects)
		ft_eprintf("malloc args or redirects");
	while (has_next(expression))
	{
		parse_arguments(sh_data, expression, args);
		parse_redirects(sh_data, expression, redirects);
	}
	ft_printf("size args %d\n", args->size);
	ft_printf("size redi %d\n", redirects->size);
	t_vector	*t;
	ft_putendl_fd("args", 1);
	while (has_next(args))
	{
		t = *(t_vector **)next(args);
		ft_putendl_fd(t->mem, 1);
		delete(t);
	}
	ft_putendl_fd("redirects", 1);
	while (has_next(redirects))
	{
		t = *(t_vector **)next(redirects);
		ft_putendl_fd(t->mem, 1);
		delete(t);
	}
	delete(args);
	delete(redirects);
}
