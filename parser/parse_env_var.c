#include "libft.h"
#include "minishell.h"

static t_vector	*get_env_var(t_vector *expression)
{
	char		ch;
	t_vector	*str;

	str = new_vector(CHAR);
	ch = 0;
	if (!str)
		ft_eprintf("get_env_var");
	if (has_next(expression))
		ch = *(char *)next(expression);
	if (ch == '?' || ft_isdigit(ch))
	{
		str->method->push_back(str, &ch);
		return (str);
	}
	while (has_next(expression))
	{
		if (ft_isalnum(ch))
			str->method->push_back(str, &ch);
		else
			break ;
		ch = *(char *)next(expression);
	}
	previous(expression);
	return (str);
}

static void	parse_exit_status(t_sh_data *sh_data, t_vector *token)
{
	char	*s;
	int		status;

	status = sh_data->exec_params.status;
	if (status == 0 && get_signal() != 0)
		status = 128 + get_signal();
	s = ft_itoa(status);
	if (!s)
		ft_eprintf("parse_exit_status");
	token->method->add_mem(token, s, ft_strlen(s));
	free(s);
}

void	parse_env_variable(t_vector *expression,
		t_vector *token, t_sh_data *sh_data)
{
	char		*next_env;
	char		*s;
	t_vector	*parse_env;

	parse_env = get_env_var(expression);
	if (has_next(expression))
		s = get_next(expression);
	if (!parse_env->size && *s != '\'' && *s != '"')
		token->method->push_back(token, "$");
	sh_data->envp->pos = 0;
	while (parse_env->size && has_next(sh_data->envp))
	{
		next_env = *(char **)next(sh_data->envp);
		s = ft_strchr(next_env, '=');
		if (s && !ft_strncmp(next_env, parse_env->mem, parse_env->size))
		{
			s++;
			token->method->add_mem(token, s, ft_strlen(s));
			break ;
		}
	}
	if (!ft_strcmp(parse_env->mem, "?"))
		parse_exit_status(sh_data, token);
	delete(parse_env);
}
