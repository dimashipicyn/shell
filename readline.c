#include "libft.h"
#include "term.h"
#include "history.h"
#include "linenavigation.h"

static void	add_char(t_vector *buf, char ch, int *position)
{
	if (ft_isprint(ch))
	{
		buf->method->insert(buf, &ch, *position);
		*position += 1;
	}
}

static void	delete_char(t_vector *buf, char ch, int *position)
{
	if (ch != 127)
		return ;
	if (*position > 0)
	{
		buf->method->erase(buf, *position - 1);
		*position -= 1;
	}
}

void	close_minishell(char *s, t_vector *buf)
{
	if (*s == 4 && buf->size == 0)
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
}

void	readline(t_history *history)
{
	int			cursor;
	char		s[4];
	t_vector	*entry;

	cursor = 0;
	entry = history_get_entry(history);
	while (!ft_isnewline(*s))
	{
		if (is_empty_stdin())
			continue ;
		ft_bzero(s, 4);
		read(0, s, 3);
		close_minishell(s, entry);
		move_left(cursor);
		entry = move_history(history, s, &cursor);
		move_cursor(s, &cursor, entry->size);
		delete_char(entry, *s, &cursor);
		add_char(entry, *s, &cursor);
		command("cd", 0, 0);
		ft_putstr_fd(entry->mem, 1);
		move_left(entry->size - cursor);
	}
}
