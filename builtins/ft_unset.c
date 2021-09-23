/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 18:48:03 by tphung            #+#    #+#             */
/*   Updated: 2021/06/16 13:28:22 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"
#include "structs.h"
#include "utils.h"

int	ft_unset(char **argv, Vector(char_ptr_t) *envp)
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
			free(m_at(envp, pos));
			m_erase(envp, pos);
		}
		i++;
	}
	return (0);
}
