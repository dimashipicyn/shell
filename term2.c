#include "term.h"

int	get_term_size(void)
{
	struct winsize	wins;

	ioctl(0, TIOCGWINSZ, &wins);
	return (wins.ws_col);
}

int	is_empty_stdin(void)
{
	int	bytes;

	ioctl(0, FIONREAD, &bytes);
	if (bytes > 0)
		return (0);
	return (1);
}
