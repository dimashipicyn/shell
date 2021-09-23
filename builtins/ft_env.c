/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 14:56:44 by tphung            #+#    #+#             */
/*   Updated: 2021/06/14 19:49:48 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"
#include "vector.h"

int	ft_env(Vector(char_ptr_t) *envp)
{
	int		pos;
	char	*var_env;

	pos = -1;
	for (int i = 0; i < envp->size; i++)
	{
		var_env = m_at(envp, i);
		if (ft_strchr(var_env, '='))
			ft_printf("%s\n", var_env);
	}
	return (0);
}
