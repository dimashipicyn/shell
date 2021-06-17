#include "libft.h"
#include "minishell.h"

#define SINGLEQUOTE '\''
#define DOUBLEQUOTE '"'
#define BACKSLASH '\\'
#define DOLOR '$'

static BOOLEAN	is_correct_quote(t_vector *expression, char quote)
{
	char	sym;
	char	prev_sym;

	prev_sym = 0;
	while (has_next(expression))
	{
		sym = *(char *)next(expression);
		if (sym == quote && (prev_sym != BACKSLASH || quote == SINGLEQUOTE))
			return (TRUE);
		if (sym == BACKSLASH && prev_sym == BACKSLASH)
			prev_sym = 0;
		else
			prev_sym = sym;
	}
	return (FALSE);
}

static BOOLEAN	op_is_available(char *op)
{
	char	**opps;
	int		i;

	i = 0;
	opps = (char *[]){";", ">", "<", ">>", "<<", "|", 0};
	while (opps[i])
	{
		if (!ft_strcmp(opps[i], op))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static BOOLEAN	check_operators(t_vector *exp, char *sym)
{
	t_vector	*op;
	BOOLEAN		is_correct;

	op = new_vector(CHAR);
	if (!op)
		ft_eprintf("malloc check operators");
	is_correct = FALSE;
	op->method->push_back(op, sym);
	while (has_next(exp))
	{
		*sym = *(char *)next(exp);
		if (*sym == ' ')
			continue ;
		if (ft_strchr("><|;", *sym))
			op->method->push_back(op, sym);
		else
		{
			previous(exp);
			break ;
		}
	}
	if (op_is_available(op->mem) && (has_next(exp) || !ft_strcmp(op->mem, ";")))
		is_correct = TRUE;
	delete(op);
	return (is_correct);
}

static BOOLEAN	check_quotes(t_vector *expression, char *err)
{
	BOOLEAN	is_correct;
	char	sym;
	char	prev_sym;

	is_correct = TRUE;
	expression->pos = 0;
	sym = 0;
	while (has_next(expression))
	{
		prev_sym = sym;
		sym = *(char *)next(expression);
		if (sym == DOUBLEQUOTE && prev_sym != BACKSLASH)
			is_correct &= is_correct_quote(expression, DOUBLEQUOTE);
		else if (sym == SINGLEQUOTE && prev_sym != BACKSLASH)
			is_correct &= is_correct_quote(expression, SINGLEQUOTE);
		else if (ft_strchr("><|;", sym) && prev_sym != BACKSLASH)
			is_correct &= check_operators(expression, &sym);
		else if (sym == BACKSLASH && prev_sym == BACKSLASH)
			sym = 0;
	}
	if (sym == BACKSLASH)
		is_correct = FALSE;
	*err = sym;
	return (is_correct);
}

BOOLEAN	is_correct_syntax(t_vector *expression)
{
	BOOLEAN	is_correct;
	char	sym;

	is_correct = TRUE;
	is_correct &= check_quotes(expression, &sym);
	if (!is_correct)
		ft_fprintf(2, "%c: syntax error near unexpected token '%c'\n",
			ft_getprogname(), sym);
	return (is_correct);
}
