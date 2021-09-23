#include "minishell.h"
#include "parser.h"

static void	split_multitoken(Vector(char) *token, Vector(void_ptr_t) *tokens)
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
		m_push_back(tokens, split + it);
		it++;
	}
	if (last_elem >= 0)
	{
		m_load(token,split[last_elem], ft_strlen(split[last_elem]));
		free(split[last_elem]);
	}
	free(split);
}

static void	parse_token(t_sh_data *sh_data,
                           Iterator(char) *iterExpr, Vector(char) *token, Vector(void_ptr_t) *tokens)
{
	char		sym;
	char		prev_sym;

	prev_sym = 0;
	while (m_has_next(iterExpr))
	{
		sym = m_next(iterExpr);
		if (ft_strchr(" ><|;", sym) && prev_sym != BACKSLASH)
			break ;
		//m_next(iterExpr);
		if ((sym == SINGLEQUOTE || sym == DOUBLEQUOTE) && prev_sym != BACKSLASH)
			parse_quotes(iterExpr, token, sh_data, sym);
		else if (sym == DOLOR && prev_sym != BACKSLASH)
		{
			parse_env_variable(iterExpr, token, sh_data);
			split_multitoken(token, tokens);
		}
		else if (sym != BACKSLASH || prev_sym == BACKSLASH)
		{
			m_push_back(token, sym);
			sym = 0;
		}
		prev_sym = sym;
	}
}

Vector(char)	*get_token(Iterator(char) *iterExpr,
                       Vector(void_ptr_t) *tokens, t_sh_data *sh_data)
{
    Vector(char)	*token;

	token = new(Vector(char));
	if (!token)
		ft_eprintf("get token");
	//skip_delimiters(expression, " ");
	while (m_has_next(iterExpr)) {
	    if (m_next(iterExpr) != ' ') {
	        m_prev(iterExpr);
	        break;
	    }
	}
	parse_token(sh_data, iterExpr, token, tokens);
	return (token);
}
