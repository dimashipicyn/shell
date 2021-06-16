#include "minishell.h"

static int	g_signal;

void	quit_handler(int sig)
{
	g_signal = sig;
	ft_putendl_fd("Quit 3", 2);
}

void	int_handler(int sig)
{
	g_signal = sig;
	ft_putendl_fd("", 2);
}
