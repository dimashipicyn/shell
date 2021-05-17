#include "libft.h"

static t_vector	*get_env_var(t_vector *expression)
{
	char		ch;
	t_vector	*str;

	str = new_vector(CHAR);
	ft_assert(!!str, "parse_env_var.c", "9");
	while (has_next(expression))
	{
		ch = *(char *)next(expression);
		if (ft_isalnum(ch))
			str->method->push_back(str, &ch);
		else
		{
			previous(expression);
			break ;
		}
	}
	return (str);
}

void	parse_env_variable(t_vector *expression,
		t_vector *token, t_vector *envp)
{
	char		*next_env;
	char		*s;
	t_vector	*parse_env;

	parse_env = get_env_var(expression);
	if (!parse_env->size)
	{
		token->method->push_back(token, "$");
		delete(parse_env);
		return ;
	}
	while (has_next(envp))
	{
		next_env = *(char **)next(envp);
		s = ft_strchr(next_env, '=');
		if (!s)
			continue ;
		if (!ft_strncmp(next_env, parse_env->mem, parse_env->size))
		{
			s++;
			token->method->add_mem(token, s, ft_strlen(s));
			break ;
		}
	}
	envp->pos = 0;
	delete(parse_env);
}
