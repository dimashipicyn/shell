#include "libft.h"
#include "minishell.h"

static t_vector	*get_env_var(t_vector *expression)
{
	char		ch;
	t_vector	*str;

	str = new_vector(CHAR);
	if (!str)
		ft_eprintf("");
	while (has_next(expression))
	{
		ch = *(char *)next(expression);
		if (ft_isalnum(ch) || ch == '?')
			str->method->push_back(str, &ch);
		else
		{
			previous(expression);
			break ;
		}
	}
	return (str);
}

static void	parse_exit_status(t_sh_data *sh_data, t_vector *token)
{
	char	*status;

	status = ft_itoa((unsigned char)sh_data->exec_params.status);
	if (!status)
		ft_eprintf("ft_itoa");
	token->method->add_mem(token, status, ft_strlen(status));
	free(status);
}

void	parse_env_variable(t_vector *expression,
		t_vector *token, t_sh_data *sh_data)
{
	char		*next_env;
	char		*s;
	t_vector	*parse_env;

	parse_env = get_env_var(expression);
	if (!parse_env->size)
		token->method->push_back(token, "$");
	sh_data->envp->pos = 0;
	while (parse_env->size && has_next(sh_data->envp))
	{
		next_env = *(char **)next(sh_data->envp);
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
	if (!ft_strcmp(parse_env->mem, "?"))
		parse_exit_status(sh_data, token);
	delete(parse_env);
}
