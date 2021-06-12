/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 16:50:25 by tphung            #+#    #+#             */
/*   Updated: 2021/06/12 20:22:35 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/inc.h"
#include "../includes/utils.h"

int	ft_cd(char **args, t_vector *envp)
{
	int	pos;
	char	*dir;
	char	*old_dir;

	pos = locate_env("HOME", envp);
	if (!args || !args[1])
	{
		if (pos < 0)
		{
			ft_fprintf(2, "minishell: cd: HOME not set\n");
			return (0);
		}
		dir = *(char**)envp->method->at(envp, pos);
		dir = ft_substr(dir,\
			1 + ft_strchr(dir, '=') - dir, ft_strlen(dir));
	}
	else
		dir = ft_strdup(args[1]);
	chdir(dir);
	free(dir);
	if (errno > 0)
		ft_wprintf("cd");
	return (0);
}