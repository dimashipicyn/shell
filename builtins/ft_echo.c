/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 13:27:03 by tphung            #+#    #+#             */
/*   Updated: 2021/06/17 12:15:44 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

int	check_echo(char **args)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (args[i])
	{
		if (!ft_strcmp("-n", args[i++]))
			flag += 1;
		else
			break ;
	}
	return (flag);
}

int	ft_echo(char **args)
{
	int	flag;

	if (!args || !*args)
	{
		write(1, "\n", 1);
		return (0);
	}
	flag = check_echo(args);
	if (flag)
		args += flag;
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
