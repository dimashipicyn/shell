/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 18:48:03 by tphung            #+#    #+#             */
/*   Updated: 2021/06/12 19:38:37 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/inc.h"
#include "../includes/utils.h"

int	ft_unset(char **argv, t_vector *envp)
{
	int	i;
	int	equal;
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