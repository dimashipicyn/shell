#include "libft.h"
#include "minishell.h"
#include "parser.h"

void	parse_arguments(t_sh_data *sh_data, Iterator(char) *iterExpr)
{
    Vector(char)	    *token;
    Vector(void_ptr_t)	*args;
	char		        sym;

	args = new(Vector(void_ptr_t));
	if (!args)
		ft_eprintf("parse arguments");
	while (m_has_next(iterExpr))
	{
		sym = m_get(iterExpr);
		if (ft_strchr("<>|;", sym)) {
		    break ;
		}
		token = get_token(iterExpr, args, sh_data);
		if (token->size != 0)
		{
			m_push_back(args, token->mem);
			free(token);
		}
		else
			delete(token);
	}
	sh_data->exec_params.argv = (char **)args->mem;
	free(args);
}
