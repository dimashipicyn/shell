/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mediator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:26:52 by tphung            #+#    #+#             */
/*   Updated: 2021/06/17 19:01:34 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"
#include "structs.h"
#include "utils.h"
#include "pipe_redirects.h"

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

int	waitpid_forall(t_main *arg)
{
	pid_t	pid;

	pid = 0;
	arg->pids->pos = 0;
	while (has_next(arg->pids))
	{
		pid = *(pid_t *)next(arg->pids);
		waitpid(pid, &(arg->status), 0);
		arg->status = WEXITSTATUS(arg->status);
	}
	arg->pids->method->clear(arg->pids);
	return (0);
}

int	mediator(t_main *arg, t_vector *envp)
{
	int		flag;
	pid_t	pid;

	pid = 0;
	flag = check_flags(arg);
	vector_init(arg);
	if (!arg->argv || !*arg->argv)
	{
		do_pipe(arg);
		ft_fprintf(2, "minishell: : command not found\n");
		if (arg->pipe_in || arg->pipe_out)
			after_pipes(arg);
	}
	else
	{
		pid = launcher(arg, envp);
		if (pid > 0)
			arg->pids->method->push_front(arg->pids, &pid);
		else if ((pid == -1) || (pid == 0))
			arg->status = pid * -1;
	}
	if (flag == TRUE)
		waitpid_forall(arg);
	return (pid);
}
