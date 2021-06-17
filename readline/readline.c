#include "minishell.h"
#include "history.h"
#include "termc.h"
#include "linenavigation.h"

#define PROMPT "\033[32mminishell:> \033[0m"

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
		history_save_to_file(history, HISTORY_PATH);
		reset_input_mode();
		exit(0);
	}
}

void	check_ctrl_c(char *s, t_vector *buf, int *cursor)
{
	if (*s == 3)
	{
		buf->method->clear(buf);
		ft_putendl_fd("", 2);
		ft_putstr_fd(PROMPT, 2);
		*cursor = 0;
	}
}

t_vector	*readline(t_history *history)
{
	int			cursor;
	char		s[1000];
	t_vector	*buf;

	cursor = 0;
	buf = new_vector(CHAR);
	if (!buf)
		ft_eprintf("malloc readline");
	ft_bzero(s, 1000);
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
