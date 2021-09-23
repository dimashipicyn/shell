/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:25:56 by tphung            #+#    #+#             */
/*   Updated: 2021/06/16 16:27:15 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"
#include "structs.h"
#include "utils.h"

int	do_redir_out(t_main *arg)
{
	arg->save_fd_write = dup(1);
	fd_replacement(arg->red_out, 1);
	return (0);
}

int	do_redir_in(t_main *arg)
{
	if (arg->pipe_in == 0)
		arg->save_fd_read = dup(0);
	fd_replacement(arg->red_in, 0);
	return (0);
}

int	do_redir(t_main *arg)
{
	if (arg->red_out == -1 && arg->red_in == -1)
		return (0);
	if (arg->red_in > 0)
		do_redir_in(arg);
	if (arg->red_out > 0)
		do_redir_out(arg);
	return (1);
}
