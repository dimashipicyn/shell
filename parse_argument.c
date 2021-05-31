#include "libft.h"
#include "minishell.h"
#include "parser.h"

static char	**vector_to_argv(t_vector *args)
{
	char		**argv;
	t_vector	*token;
	int			i;

	i = 0;
	argv = (char **)ft_calloc(args->size + 1, sizeof(char *));
	if (!argv)
		ft_eprintf("malloc argv");
	args->pos = 0;
	while (has_next(args))
	{
		token = *(t_vector **)next(args);
		argv[i] = token->mem;
		i++;
	}
	argv[i] = 0;
	return (argv);
}

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
		args->method->push_back(args, &token);
	}
	sh_data->exec_params.argv = vector_to_argv(args);
	args->pos = 0;
	while (has_next(args))
	{
		token = *(t_vector **)next(args);
		free(token);
	}
	delete(args);
}
