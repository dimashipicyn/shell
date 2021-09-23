#include "minishell.h"

static void	readline_stdin(Vector(char) *entry, char **bufptr)
{
	char	*s;
	BOOLEAN	squote;
	BOOLEAN	dquote;

	s = *bufptr;
	squote = FALSE;
	dquote = FALSE;
	while (*s && (!ft_isnewline(*s) || squote || dquote))
	{
		if (*s == '"' && squote)
			dquote = ~dquote;
		if (*s == '\'' && dquote)
			squote = ~squote;
		m_push_back(entry, *s);
		s++;
	}
	while (*s && ft_isnewline(*s))
		s++;
	*bufptr = s;
}

void	interpret_stdin(t_sh_data *sh_data)
{
    Vector(char)	*entry;
	char		    buf[1001];
	char		    *bufptr;

	entry = new(Vector(char));
	if (!entry)
		ft_eprintf("interpret_stdin");
	ft_bzero(buf, 1001);
	read(0, buf, 1000);
	bufptr = buf;
	while (*bufptr)
	{
		readline_stdin(entry, &bufptr);
		if (is_correct_syntax(entry))
			parse_expression(sh_data, entry);
		m_clear(entry);
	}
	delete(entry);
}
