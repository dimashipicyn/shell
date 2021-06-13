/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 18:48:03 by tphung            #+#    #+#             */
/*   Updated: 2021/06/13 17:03:42 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"
#include "utils.h"

int	ft_unset(char **argv, t_vector *envp)
{
	int	i;
	int	pos;

	i = 1;
	pos = -1;
	while (argv[i])
	{
		pos = locate_env(argv[i], envp);
		if (pos >= 0)
		{
			free(*(char**)envp->method->at(envp, pos));
			envp->method->erase(envp, pos);
		}
		i++;
	}
	return (0);
}
