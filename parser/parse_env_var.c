#include "libft.h"
#include "minishell.h"

static Vector(char)	*get_env_var(Iterator(char) *iterExpr)
{
	char		    ch;
    Vector(char)	*str;

	str = new(Vector(char));
	ch = 0;
	if (!str)
		ft_eprintf("get_env_var");
	if (m_has_next(iterExpr))
		ch = m_next(iterExpr);
	if (ch == '?' || ft_isdigit(ch))
	{
		m_push_back(str, ch);
		return (str);
	}
	while (m_has_next(iterExpr))
	{
		if (ft_isalnum(ch))
			m_push_back(str, ch);
		else
			break ;
		ch = m_next(iterExpr);
	}
	m_prev(iterExpr);
	return (str);
}

static void	parse_exit_status(t_sh_data *sh_data, Vector(char) *token)
{
	char	*s;
	int		status;

	status = sh_data->exec_params.status;
	if (status == 0 && get_signal() != 0)
		status = 128 + get_signal();
	s = ft_itoa(status);
	if (!s)
		ft_eprintf("parse_exit_status");
	m_add_mem(token, s, ft_strlen(s));
	free(s);
}

void	parse_env_variable(Iterator(char) *iterExpr,
                           Vector(char) *token, t_sh_data *sh_data)
{
	char		    *next_env;
	char		    ch;
	char            *s;
    Vector(char)	*parse_env;

	parse_env = get_env_var(iterExpr);
	if (m_has_next(iterExpr))
		ch = m_next(iterExpr); // get_next FIXME
	if (!parse_env->size && ch != '\'' && ch != '"')
		m_push_back(token, '$');
	//while (parse_env->size && has_next(sh_data->envp))
	for (int i = 0; i < sh_data->envp->size; i++)
	{
		next_env = m_at(sh_data->envp, i);
		s = ft_strchr(next_env, '=');
		if (s && !ft_strncmp(next_env, parse_env->mem, parse_env->size))
		{
			s++;
			m_add_mem(token, s, ft_strlen(s));
			break ;
		}
	}
	if (!ft_strcmp(parse_env->mem, "?"))
		parse_exit_status(sh_data, token);
	delete(parse_env);
}
