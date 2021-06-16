/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mediator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:26:52 by tphung            #+#    #+#             */
/*   Updated: 2021/06/16 13:48:23 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"
#include "structs.h"
#include "utils.h"

char	**matrix_dup(char	**src)
{
	char	**dest;
	int		len;

	len = 0;
	while (src[len])
		len++;
	dest = malloc(sizeof(char *) * (1 + len));
	dest[len] = 0;
	len = 0;
	while (src[len])
	{
		dest[len] = ft_strdup(src[len]);
		len++;
	}
	return (dest);
}

int	check_flags(t_main *arg)
{
	int	res;

	res = TRUE;
	if (arg->pipe_out == TRUE)
		res = FALSE;
	return (res);
}

void	vector_init(t_main *arg)
{
	if (arg->pids == NULL)
	{
		arg->pids = new_vector(sizeof(pid_t));
		if (arg->pids == NULL)
			ft_eprintf("mediator:");
	}
}

int	mediator(t_main *arg, t_vector *envp)
{
	int		flag;
	pid_t	pid;

	flag = check_flags(arg);
	vector_init(arg);
	pid = launcher(arg, envp);
	if (pid)
	{
		if (arg->pids->method->push_front(arg->pids, &pid) == FALSE)
			ft_eprintf("mediator:");
	}
	if (flag == TRUE)
	{
		arg->pids->pos = 0;
		while (has_next(arg->pids))
		{
			pid = *(pid_t *)next(arg->pids);
			waitpid(pid, &(arg->status), 0);
			arg->status = WEXITSTATUS(arg->status);
		}
		arg->pids->method->clear(arg->pids);
	}
	return (0);
}
