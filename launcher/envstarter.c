/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envstarter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 18:18:05 by tphung            #+#    #+#             */
/*   Updated: 2021/06/16 19:34:44 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"
#include "structs.h"
#include "utils.h"

void	dunction(t_vector *envp, int pos)
{
	char	*str[3];
	int		lvl;

	str[0] = *(char **)envp->method->at(envp, pos);
	str[1] = ft_strchr(str[0], '=');
	lvl = ft_atoi(str[1] + 1);
	if (lvl <= 0)
		str[1] = ft_strdup("SHLVL=1");
	else
	{
		str[2] = ft_itoa(lvl + 1);
		str[1] = ft_strjoin("SHLVL=", str[2]);
		free(str[2]);
	}
	str[2] = NULL;
	ft_export(str, envp);
	free(str[1]);
}

void	do_shlvl(t_vector *envp)
{
	int		pos;
	char	*str;

	pos = locate_env("SHLVL=", envp);
	if (pos < 0)
	{
		str = ft_strdup("SHLVL=1");
		envp->method->push_back(envp, &str);
	}
	else
		dunction(envp, pos);
}

void	do_minishell(t_vector *envp)
{
	char	*argv[4];

	argv[0] = "SHELL=minishell";
	argv[1] = "SHELL=minishell";
	argv[2] = "SHLVL=1";
	argv[3] = NULL;
	ft_export(argv, envp);
}

void	env_starter(t_vector *envp)
{
	int		pos;
	char	*str;

	pos = locate_env("SHELL", envp);
	if (pos < 0)
	{
		do_minishell(envp);
	}
	else
	{
		str = *(char **)envp->method->at(envp, pos);
		if (ft_strcmp("SHELL=minishell", str) == 0)
			do_shlvl(envp);
		else
			do_minishell(envp);
	}
}
