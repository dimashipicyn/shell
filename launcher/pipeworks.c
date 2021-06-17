/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeworks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:59:49 by tphung            #+#    #+#             */
/*   Updated: 2021/06/17 16:23:57 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"
#include "structs.h"
#include "utils.h"

int	fd_replacement(int old_fd, int new_fd)
{
	int		i;

	errno = 0;
	i = dup2(old_fd, new_fd);
	if (i < 0)
		ft_eprintf("fd_replacement:");
	return (0);
}

int	open_pipe(t_main *arg)
{
	int		file_des[2];
	int		i;

	errno = 0;
	i = pipe(file_des);
	if (i != 0)
		ft_eprintf("open_pipe:");
	arg->fd_read = file_des[0];
	arg->fd_write = file_des[1];
	return (0);
}

int	do_pipe(t_main *arg)
{
	if (arg->pipe_out == 1)
	{
		if (arg->pipe_in == 1)
		{
			arg->save_fd_read = dup(0);
			fd_replacement(arg->fd_read, 0);
			close(arg->fd_read);
		}
		open_pipe(arg);
		if (arg->pipe_in == 0)
			arg->save_fd_write = dup(1);
		fd_replacement(arg->fd_write, 1);
		close(arg->fd_write);
	}
	if (arg->pipe_in == 1 && arg->pipe_out == 0)
	{
		arg->save_fd_read = dup(0);
		fd_replacement(arg->fd_read, 0);
		fd_replacement(arg->save_fd_write, 1);
		close(arg->fd_read);
		close(arg->save_fd_write);
	}
	return (0);
}

void	after_pipes(t_main *arg)
{
	if (arg->pipe_in || arg->red_in > 0)
	{
		fd_replacement(arg->save_fd_read, 0);
		close(arg->save_fd_read);
	}
	if (arg->red_out > 0 && arg->pipe_out == 0)
	{
		fd_replacement(arg->save_fd_write, 1);
		close(arg->save_fd_write);
	}
}
