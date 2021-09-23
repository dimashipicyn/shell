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
#include "vector.h"

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
		arg->pids = new(Vector(int));
		if (arg->pids == NULL)
			ft_eprintf("mediator:");
	}
}

int	mediator(t_main *arg, Vector(char_ptr_t) *envp)
{
	int		flag;
	pid_t	pid;

	flag = check_flags(arg);
	vector_init(arg);
	pid = launcher(arg, envp);
	if (pid)
	{
		if (m_push_front(arg->pids, pid) == FALSE)
			ft_eprintf("mediator:");
	}
	if (flag == TRUE)
	{
		for (int i = 0; i < arg->pids->size; i++)
		{
			pid = m_at(arg->pids, i);
			waitpid(pid, &(arg->status), 0);
			arg->status = WEXITSTATUS(arg->status);
		}
		m_clear(arg->pids);
	}
	return (0);
}
