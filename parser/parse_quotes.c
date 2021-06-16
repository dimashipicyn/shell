#include "libft.h"
#include "minishell.h"

static BOOLEAN	parse_single_quotes(t_vector *expression, t_vector *token)
{
	char		*ch;

	while (has_next(expression))
	{
		ch = next(expression);
		if (*ch == '\'')
			return (TRUE);
		token->method->push_back(token, ch);
	}
	return (FALSE);
}

static BOOLEAN	parse_double_quotes(t_vector *expression,
		t_vector *token, t_sh_data *sh_data)
{
	char		sym;
	char		prev_sym;

	sym = 0;
	while (has_next(expression))
	{
		prev_sym = sym;
		sym = *(char *)next(expression);
		if (sym == '"' && prev_sym !='\\')
			return (TRUE);
		else if (sym == '$' && prev_sym !='\\')
			parse_env_variable(expression, token, sh_data);
		else if (sym == '\\' && prev_sym == '\\')
			sym = 0;
		else
			token->method->push_back(token, &sym);
		if ((sym == '"' || sym == '$') && prev_sym == '\\')
			token->method->erase(token, token->size - 2);
	}
	return (FALSE);
}

BOOLEAN	parse_quotes(t_vector *expression, t_vector *token, t_sh_data *sh_data, char quote)
{
	BOOLEAN	ret;

	if (quote == '\'')
		ret = parse_single_quotes(expression, token);
	if (quote == '"')
		ret = parse_double_quotes(expression, token, sh_data);
	return (ret);
}
