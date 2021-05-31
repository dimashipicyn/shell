#include "libft.h"

void	ft_assert(BOOLEAN expr, char *file, char *line)
{
	if (!expr)
	{
		ft_printf("Assertion! file: %s, line: %s.\n", file, line);
		exit(1);
	}
}
