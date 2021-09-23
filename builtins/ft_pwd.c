/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 16:21:49 by tphung            #+#    #+#             */
/*   Updated: 2021/06/13 15:52:17 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

int	ft_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	free(str);
	return (0);
}
