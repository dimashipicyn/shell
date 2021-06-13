#include "minishell.h"
#include <termios.h>
#include <term.h>

static char				g_room_termtype[2048];
static char				*g_termtype;
static char				g_buff[100];
static char				*g_buffer;

/* Установка терминала в неканонический режим */
static struct termios	g_save_attr;

void	reset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_save_attr);
}

void	set_input_mode(void)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &g_save_attr);
	tcgetattr (STDIN_FILENO, &attr);
	attr.c_lflag &= ~(ICANON | ECHO | ISIG);
	tcsetattr (STDIN_FILENO, TCSAFLUSH, &attr);
}
/* Clear ICANON and ECHO. */
/* end set terminal */

//необходима для tputs
static int	ft_putint(int c)
{
	return (write(2, &c, 1));
}

void	command(char *s, int x, int y)
{
	g_buffer = g_buff;
	tputs(tgoto(tgetstr(s, &g_buffer), y, x), 0, ft_putint);
	g_buffer = g_buff;
	ft_bzero(g_buffer, 100);
}

BOOLEAN	init_term(void)
{
	if (!isatty(STDIN_FILENO))
		return (FALSE);
	g_termtype = getenv("TERM");
	if (g_termtype == NULL || tgetent(g_room_termtype, g_termtype) != 1)
		return (FALSE);
	return (TRUE);
}
