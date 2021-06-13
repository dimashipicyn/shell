#include "inc.h"

int ft_errors(int code)
{
	write(2, "minishell:", 10);
	printf("%s\n", strerror(errno));
	return (code);
}
