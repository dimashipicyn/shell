#include "libft.h"
#include "term.h"
#include "history.h"
#include "linenavigation.h"

static void	add_char(t_vector *buf, char *s, int *position)
{
	while (*s && ft_isprint(*s))
	{
		buf->method->insert(buf, s, *position);
		*position += 1;
		s++;
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

void	close_minishell(char *s, t_history *history, BOOLEAN emptybuf)
{
	if (*s == 4 && emptybuf)
	{
		ft_putendl_fd("exit", 1);
		history_save_to_file(history, "test.txt");
		reset_input_mode();
		exit(0);
	}
}

void	readline(t_history *history)
{
	int			cursor;
	char		s[1000];
	t_vector	*entry;
	t_vector	*buf;

	cursor = 0;
	entry = history_get_entry(history);
	buf = new_vector(CHAR);
	if (!buf)
		ft_eprintf("malloc readline");
	ft_bzero(s, 1000);
	while (!ft_isnewline(*s))
	{
		ft_bzero(s, 1000);
		read(0, s, 1000);
		move_left(cursor);
		close_minishell(s, history, !buf->size);
		navigation(buf, history, s, &cursor);
		delete_char(buf, *s, &cursor);
		add_char(buf, s, &cursor);
		command("cd", 0, 0);
		ft_putstr_fd(buf->mem, 1);
		move_left(buf->size - cursor);
	}
	entry->method->load(entry, buf->mem, buf->size);
}
