/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mediator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:26:52 by tphung            #+#    #+#             */
/*   Updated: 2021/05/28 14:38:06 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/inc.h"
#include "./includes/structs.h"

int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_cd(char **args, char **root_path);
pid_t	launcher(t_main *arg, t_vector *envp);

char	**matrix_dup(char	**src)
{
	char	**dest;
	int		len;

	len = 0;
	while (src[len])
		len++;
	dest = malloc(sizeof(char*) * (1 + len));
	dest[len] = 0;
	len = 0;
	while(src[len])
	{
		dest[len] = ft_strdup(src[len]);
		len++;
	}
	return (dest);
}

int		check_flags(t_main *arg)
{
	int	res;

	res = TRUE;
	if (arg->pipe_in != FALSE)
		res = FALSE;
	if (arg->pipe_in != FALSE)
		res = FALSE;
	if (arg->red_in != -1)
		res = FALSE;
	if (arg->red_out != -1)
		res = FALSE;
	return (res);
}

int		mediator(t_main *arg, t_vector *envp)
{
	int		flag;
	pid_t	pid;

	flag = check_flags(arg);
	if (arg->pids == NULL)
	{
		arg->pids = new_vector(sizeof(pid_t));
		if (arg->pids == NULL)
			return (-1);//ERROR
	}
	pid = launcher(arg, envp);
	if (arg->pids->method->push_back(arg->pids, &pid) == FALSE)
		return(-1);//ERROR
	if (flag == TRUE)
	{
		while (has_next(arg->pids))
		{
			pid = *(pid_t*)next(arg->pids);
			waitpid(pid, &(arg->status), 0);
		}
		arg->pids->method->clear(arg->pids);
	}
	return (0);
}