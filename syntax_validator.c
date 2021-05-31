#include "libft.h"
#include "minishell.h"

#define SINGLEQUOTE '\''
#define DOUBLEQUOTE '"'
#define BACKSLASH '\\'
#define DOLOR '$'

static BOOLEAN		is_correct_quotes(t_vector *expression, char quote)
{
	char	sym;
	char	prev_sym;
	BOOLEAN	in_quotes;
	
	expression->pos = 0;
	prev_sym = 0;
	in_quotes = FALSE;
	while (has_next(expression))
	{
		sym = *(char *)next(expression);
		if (sym == quote && sym != BACKSLASH)
		{
			if (in_quotes == FALSE)
				in_quotes = TRUE;
			else
				in_quotes = FALSE;
		}
		if (sym == BACKSLASH && prev_sym == BACKSLASH)
			prev_sym = 0;
		else
			prev_sym = sym;
	}
	return (!in_quotes);
}

BOOLEAN	is_correct_syntax(t_vector *expression)
{
	BOOLEAN	is_correct;

	is_correct = TRUE;
	is_correct &= is_correct_quotes(expression, DOUBLEQUOTE);
	is_correct &= is_correct_quotes(expression, SINGLEQUOTE);
	return (is_correct);
}
