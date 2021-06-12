/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 14:56:44 by tphung            #+#    #+#             */
/*   Updated: 2021/06/12 15:07:07 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/inc.h"

int	ft_env(t_vector *envp)
{
	int		pos;
	int		equal;
	char	*var_env;

	pos = -1;
	envp->pos = 0;
	while (has_next(envp))
	{
		//printf("POS in ENVP = %d\n", envp->pos);
		var_env = *(char**)next(envp);
		printf("FOUND in ENVP = %s\n", var_env);
		//equal = ft_strchr(var_env, '=') - var_env; 
		//if (ft_strncmp(var_env, var, equal + 1) == 0)
		//{
		//	return (envp->pos - 1);
		//}
		//printf("VAR in ENVP = %s\n", var_env);
	}
	envp->pos = 0;
	return (0);
}