/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:11:22 by tphung            #+#    #+#             */
/*   Updated: 2021/06/17 14:16:56 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"
#include "structs.h"
#include "utils.h"
#include "pipe_redirects.h"

pid_t	fork_execve(char **argv, char **envp, char *path_name)
{
	int		stat;
	pid_t	pid;

	pid = fork();
	stat = 123;
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		errno = 0;
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		stat = execve(path_name, argv, envp);
		ft_wprintf("%s", path_name);
		exit(stat);
	}
	return (pid);
}

pid_t	fork_builtins(char **argv, t_vector *envp, int flag)
{
	pid_t	pid;

	pid = 0;
	if (flag == 1)
		pid = ft_echo(argv + 1);
	else if (flag == 4)
		pid = ft_export(argv, envp);
	else if (flag == 2)
		pid = ft_cd(argv, envp);
	else if (flag == 3)
		pid = ft_pwd();
	else if (flag == 6)
		pid = ft_env(envp);
	else if (flag == 7)
		exit(0);
	else if (flag == 5)
		pid = ft_unset(argv, envp);
	return (pid);
}

int	builtins(char *name)
{
	if (!ft_strcmp(name, "echo"))
		return (1);
	if (!ft_strcmp(name, "cd"))
		return (2);
	if (!ft_strcmp(name, "pwd"))
		return (3);
	if (!ft_strcmp(name, "export"))
		return (4);
	if (!ft_strcmp(name, "unset"))
		return (5);
	if (!ft_strcmp(name, "env"))
		return (6);
	if (!ft_strcmp(name, "exit"))
		return (7);
	if (!ft_strcmp(name, "env_start"))
		return (8);
	return (FALSE);
}

pid_t	choose_fork(t_main *arg, t_vector *envp, char *path_name, int flag)
{
	pid_t	ret;

	ret = -1;
	if (path_name)
	{
		ret = fork_execve(arg->argv, envp->mem, path_name);
		free(path_name);
	}
	else if (flag)
		ret = fork_builtins(arg->argv, envp, flag);
	return (ret);
}

int	launcher(t_main *arg, t_vector *envp)
{
	char	*str;
	pid_t	ret;
	int		flag;

	ret = -1;
	errno = 0;
	str = NULL;
	flag = FALSE;
	if (ft_strchr("./", **arg->argv))
		str = ft_strdup(*arg->argv);
	else
		flag = builtins(*(arg->argv));
	if (flag == FALSE && !str)
		str = filename_parser(*(arg->argv), envp->mem);
	do_pipe(arg);
	do_redir(arg);
	ret = choose_fork(arg, envp, str, flag);
	if ((*arg->argv && (ret < 0)) || (!str && ret < 0))
		ft_wprintf("%s", *(arg->argv));
	after_pipes(arg);
	return (ret);
}
