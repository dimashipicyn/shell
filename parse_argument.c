#include "libft.h"
#include "minishell.h"
#include "parser.h"

void	parse_arguments(t_sh_data *sh_data, t_vector *expression)
{
	t_vector	*token;
	t_vector	*args;
	char		sym;

	args = new_vector(PTR);
	if (!args)
		ft_eprintf("malloc args");
	while (has_next(expression))
	{
		sym = *(char *)get_next(expression);
		if (ft_strchr("<>|;", sym))
			break ;
		token = get_token(expression, args, sh_data);
		if (token->size != 0)
		{
			args->method->push_back(args, &(token->mem));
			free(token);
		}
		else
			delete(token);
	}
	sh_data->exec_params.argv = args->mem;
	free(args);
}
