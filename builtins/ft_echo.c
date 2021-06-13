/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 13:27:03 by tphung            #+#    #+#             */
/*   Updated: 2021/06/13 13:02:05 by lbespin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

int	check_echo(char *str)
{
	if (ft_strcmp("-n", str))
		return (0);
	return (1);
}

int	ft_echo(char **args)
{
	int	flag;

	if (!args || !*args)
	{
		write(1, "\n", 1);
		return (0);
	}
	flag = check_echo(*args);
	if (flag)
		args++;
	while (*args)
	{
		write(1, *args, ft_strlen(*args));
		args++;
		if (*args)
			write(1, " ", 1);
		else if (!flag)
			write(1, "\n", 1);
	}
	return (0);
}
