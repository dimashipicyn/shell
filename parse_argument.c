#include "libft.h"
#include "minishell.h"
#include "parser.h"

void	parse_arguments(t_sh_data *sh_data, t_vector *expression)
{
	t_vector	*token;
	t_vector	*args;

	args = new_vector(PTR);
	if (!args)
		ft_eprintf("malloc args");
	while (has_next(expression))
	{
		token = get_token(expression, args, sh_data);
		if (token->size == 0)
		{
			delete(token);
			break ;
		}
		args->method->push_back(args, &(token->mem));
		free(token);
	}
	sh_data->exec_params.argv = args->mem;
	free(args);
}
