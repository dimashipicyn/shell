#include "libft.h"
#include "minishell.h"

static BOOLEAN	parse_single_quotes(Iterator(char) *iterExpr, Vector(char) *token)
{
	char		ch;

	while (m_has_next(iterExpr))
	{
		ch = m_next(iterExpr);
		if (ch == '\'')
			return (TRUE);
		m_push_back(token, ch);
	}
	return (FALSE);
}

static BOOLEAN	parse_double_quotes(Iterator(char) *iterExpr,
                                      Vector(char) *token, t_sh_data *sh_data)
{
	char		sym;
	char		prev_sym;

	sym = 0;
	while (m_has_next(iterExpr))
	{
		prev_sym = sym;
		sym = m_next(iterExpr);
		if (sym == '"' && prev_sym !='\\')
			return (TRUE);
		else if (sym == '$' && prev_sym !='\\')
			parse_env_variable(iterExpr, token, sh_data);
		else if (sym == '\\' && prev_sym == '\\')
			sym = 0;
		else
			m_push_back(token, sym);
		if ((sym == '"' || sym == '$') && prev_sym == '\\')
			m_erase(token, token->size - 2);
	}
	return (FALSE);
}

BOOLEAN	parse_quotes(Iterator(char) *iterExpr, Vector(char) *token,
		t_sh_data *sh_data, char quote)
{
	BOOLEAN	ret;

	if (quote == '\'')
		ret = parse_single_quotes(iterExpr, token);
	if (quote == '"')
		ret = parse_double_quotes(iterExpr, token, sh_data);
	return (ret);
}
