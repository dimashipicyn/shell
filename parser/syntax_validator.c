#include "libft.h"
#include "minishell.h"

#define SINGLEQUOTE '\''
#define DOUBLEQUOTE '"'
#define BACKSLASH '\\'
#define DOLOR '$'

static BOOLEAN	is_correct_quote(Iterator(char) *iter, char quote)
{
	char	sym;
	char	prev_sym;

	prev_sym = 0;
	while (m_has_next(iter))
	{
		sym = m_next(iter);
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

static BOOLEAN	check_operators(Iterator(char) *iter, char *sym)
{
    Vector(char)	*op;
	BOOLEAN		    is_correct;

	op = new(Vector(char));
	if (!op)
		ft_eprintf("malloc check operators");
	is_correct = FALSE;
	m_push_back(op, *sym);
	while (m_has_next(iter))
	{
		*sym = m_next(iter);
		if (*sym == ' ')
            continue;
		if (ft_strchr("><|;", *sym))
		    m_push_back(op, *sym);
		else {
            m_prev(iter);
            break;
		}
	}
	if (op_is_available(op->mem) && (m_has_next(iter) || !ft_strcmp(op->mem, ";")))
		is_correct = TRUE;
	delete(op);
	return (is_correct);
}

static BOOLEAN	check_quotes(Iterator(char) *iter)
{
	BOOLEAN	is_correct;
	char	sym;
	char	prev_sym;

	is_correct = TRUE;
	sym = 0;
	while (m_has_next(iter) && is_correct)
	{
		prev_sym = sym;
		sym = m_next(iter);
		if (sym == DOUBLEQUOTE && prev_sym != BACKSLASH)
			is_correct &= is_correct_quote(iter, DOUBLEQUOTE);
		else if (sym == SINGLEQUOTE && prev_sym != BACKSLASH)
			is_correct &= is_correct_quote(iter, SINGLEQUOTE);
		else if (ft_strchr("><|;", sym) && prev_sym != BACKSLASH)
			is_correct &= check_operators(iter, &sym);
		else if (sym == BACKSLASH && prev_sym == BACKSLASH)
			sym = 0;
	}
	if (sym == BACKSLASH)
		is_correct = FALSE;
	if (!is_correct)
	    ft_fprintf(2, "%s: syntax error near unexpected token '%c'\n",
                   getprogname(), sym);
	return (is_correct);
}

BOOLEAN	is_correct_syntax(Vector(char) *expression)
{
	BOOLEAN	        is_correct;
    Iterator(char)  *iter;

    iter = $(Iterator(char), expression);
	is_correct = TRUE;
	is_correct &= check_quotes(iter);
	return (is_correct);
}
