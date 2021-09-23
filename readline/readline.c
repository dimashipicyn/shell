#include "minishell.h"
#include "history.h"
#include "termc.h"
#include "linenavigation.h"

static void	add_char(Vector(char) *buf, char *s, int *position)
{
	while (*s && ft_isprint(*s))
	{
		m_insert(buf, *s, *position);
		*position += 1;
		s++;
	}
}

static void	delete_char(Vector(char) *buf, char ch, int *position)
{
	if (ch != 127)
		return ;
	if (*position > 0)
	{
		m_erase(buf, *position - 1);
		*position -= 1;
	}
}

void	close_minishell(char *s, t_history *history, BOOLEAN emptybuf)
{
	if (*s == 4 && emptybuf)
	{
		ft_putendl_fd("exit", 1);
		history_save_to_file(history, HISTORY_PATH);
		reset_input_mode();
		exit(0);
	}
}

void	check_ctrl_c(char *s, Vector(char) *buf, int *cursor)
{
	if (*s == 3)
	{
		m_clear(buf);
		ft_putendl_fd("", 2);
		ft_putstr_fd(PROMPT, 2);
		*cursor = 0;
	}
}

Vector(char)	*readline(t_history *history)
{
	int			    cursor;
	char		    s[1000];
    Vector(char)	*buf;

	cursor = 0;
	buf = new(Vector(char));
	if (!buf)
		ft_eprintf("malloc readline");
	memset(s, 0, 1000);
	while (!ft_isnewline(*s))
	{
		move_left(buf->size - cursor);
		ft_bzero(s, 1000);
		read(0, s, 1000);
		move_left(cursor);
		close_minishell(s, history, !buf->size);
		check_ctrl_c(s, buf, &cursor);
		navigation(buf, history, s, &cursor);
		delete_char(buf, *s, &cursor);
		add_char(buf, s, &cursor);
		command("cd", 0, 0);
		ft_putstr_fd(buf->mem, 2);
	}
	return (buf);
}
