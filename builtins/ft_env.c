/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 14:56:44 by tphung            #+#    #+#             */
/*   Updated: 2021/06/13 19:58:20 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

int	ft_env(t_vector *envp)
{
	int		pos;
	char	*var_env;

	pos = -1;
	envp->pos = 0;
	while (has_next(envp))
	{
		var_env = *(char**)next(envp);
		ft_printf("%s\n", var_env);
	}
	envp->pos = 0;
	return (0);
}
