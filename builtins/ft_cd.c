/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 16:50:25 by tphung            #+#    #+#             */
/*   Updated: 2021/06/16 13:28:07 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"
#include "structs.h"
#include "utils.h"

char	*envp_var_eject(Vector(char_ptr_t) *envp, int src_pos)
{
	char	*res;

	res = m_at(envp, src_pos);
	res = ft_substr(res,1 + ft_strchr(res, '=') - res, ft_strlen(res));
	return (res);
}

int	var_export(Vector(char_ptr_t) *envp, int dest_pos, char *var, char *dest_var_name)
{
	char		*dest;

	dest = ft_strjoin(dest_var_name, var);
	free(m_at(envp, dest_pos));
	m_erase(envp, dest_pos);
	m_insert(envp, dest, dest_pos);
	return (0);
}

int	pwd_export(Vector(char_ptr_t) *envp, char *old_pwd)
{
	int		pos_pwd;
	int		pos_old;
	char	*var;

	pos_pwd = locate_env("PWD", envp);
	pos_old = locate_env("OLDPWD", envp);
	if (pos_old >= 0 && pos_pwd >= 0)
	{
		var = envp_var_eject(envp, pos_pwd);
		var_export(envp, pos_old, var, "OLDPWD=");
		free(var);
	}
	else if (pos_old >= 0)
		var_export(envp, pos_old, old_pwd, "OLDPWD=");
	if (pos_pwd >= 0)
	{
		var = getcwd(NULL, 0);
		var_export(envp, pos_pwd, var, "PWD=");
		free(var);
	}
	return (0);
}

int	ft_cd(char **args, Vector(char_ptr_t) *envp)
{
	int		pos;
	char	*dir;
	char	*pwd;

	if (!args || !args[1])
	{
		pos = locate_env("HOME", envp);
		if (pos < 0)
		{
			ft_fprintf(2, "minishell: cd: HOME not set\n");
			return (0);
		}
		dir = envp_var_eject(envp, pos);
	}
	else
		dir = ft_strdup(args[1]);
	pwd = getcwd(NULL, 0);
	chdir(dir);
	if (errno > 0)
		ft_wprintf("cd");
	else
		pwd_export(envp, pwd);
	free(dir);
	free(pwd);
	return (0);
}
