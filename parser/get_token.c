#include "minishell.h"
#include "parser.h"

static void	split_multitoken(t_vector *token, t_vector *tokens)
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
		token->method->load(token,
			split[last_elem], ft_strlen(split[last_elem]));
		free(split[last_elem]);
	}
	free(split);
}

static void	parse_token(t_sh_data *sh_data,
		t_vector *expression, t_vector *token, t_vector *tokens)
{
	char		sym;
	char		prev_sym;

	prev_sym = 0;
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
		{
			token->method->push_back(token, &sym);
			sym = 0;
		}
		prev_sym = sym;
	}
}

t_vector	*get_token(t_vector *expression,
			t_vector *tokens, t_sh_data *sh_data)
{
	t_vector	*token;

	token = new_vector(CHAR);
	if (!token)
		ft_eprintf("get token");
	skip_delimiters(expression, " ");
	parse_token(sh_data, expression, token, tokens);
	return (token);
}
