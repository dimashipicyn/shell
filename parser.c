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
		ft_eprintf("allocation failed");
	prev_sym = 0;
	skip_delimiters(expression, " ");
	while (has_next(expression))
	{
		sym = *(char *)next(expression);
		if (ft_strchr(" ><|;", sym))
			break ;
		if ((sym == SINGLEQUOTE || sym == DOUBLEQUOTE) && prev_sym != BACKSLASH)
			parse_quotes(expression, token, sh_data, sym);
		else if (sym == DOLOR && prev_sym != BACKSLASH)
		{
			parse_env_variable(expression, token, sh_data);
			split_multitoken(token, tokens);
		}
		else if (sym != BACKSLASH || prev_sym == BACKSLASH)
			token->method->push_back(token, &sym);
		prev_sym = sym;
	}
	return (token);
}

void	parse_expression(t_sh_data *sh_data, t_vector *expression)
{
	t_vector	*tokens;
	t_vector	*token;

	tokens = new_vector(PTR);
	while (has_next(expression))
	{
		token = get_token(expression, tokens, sh_data);
		tokens->method->push_back(tokens, &token);
	}
	t_vector	*t;
	while (has_next(tokens))
	{
		t = *(t_vector **)next(tokens);
		ft_putendl_fd(t->mem, 1);
		delete(t);
	}
	delete(tokens);
}
