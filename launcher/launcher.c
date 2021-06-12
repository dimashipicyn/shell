/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:11:22 by tphung            #+#    #+#             */
/*   Updated: 2021/06/12 19:38:21 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/inc.h"
#include "./includes/structs.h"
#include "./includes/utils.h"

int			check_exist(char **path, char *file)
{
	int				i;
	DIR				*papka;
	struct dirent	*example;

	i = 0;
	while(path[i])
	{
		papka = 0;
		if((papka = opendir(path[i])))
		{
			while ((example = readdir(papka)))
			{
				if (ft_strcmp(example->d_name, file) == 0)
				{
					closedir(papka);
					return (i);
				}
			}
			closedir(papka);
		}
		i++;
	}
	return (-1);
}

char		*path_join(char *path_str, char *name)
{
	char	*tmp;
	char	*path_name;

	tmp = ft_strjoin(path_str, "/");
	if (!tmp)
		return (0);
	path_name = ft_strjoin(tmp, name);
	free(tmp);
	if (!path_name)
		return (0);
	return (path_name);
}

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
		//ft_errors(0);
		exit(stat);
	}
	ft_printf("exec pid %d\n", pid);
	return (pid);
}

char	*filename_parser(char *filename, char **envp)
{
	int		i;
	char	**path_str;
	char	*str;
	char	delim;

	i = 0;
	delim = ':';
	if (!filename)
		return(NULL);
	if (ft_strchr("./", filename[0]))
		return (ft_strdup(filename));
	while(ft_strncmp(envp[i++], "PATH=", 5))
		;
	str = envp[--i];
	path_str = ft_split(str + 5, delim);
	i = check_exist(path_str, filename);
	if (i < 0)
	{
		ft_free_array_ptr((void**)path_str);
		return (NULL);
	}
	str = path_join(path_str[i], filename);
	ft_free_array_ptr((void**)path_str);
	return (str);
}

int	open_pipe(t_main *arg)
{
	int		file_des[2];
	int		i;

	errno = 0;
	i = pipe(file_des);
	if (i != 0)
	{
		//ft_errors(0);
		exit(1);
	}
	arg->fd_read = file_des[0];
	arg->fd_write = file_des[1];
	return (0);
}

int	fd_replacement(int old_fd, int new_fd)
{
	int		i;

	errno = 0;
	i = dup2(old_fd, new_fd);
	if (i < 0)
	{
		//ft_errors(0);
		exit(1);
	}
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
		}
		open_pipe(arg);
		if (arg->pipe_in == 0)
			arg->save_fd_write = dup(1);
		fd_replacement(arg->fd_write, 1);
		close(arg->fd_write);
	}
	if (arg->pipe_in == 1)
	{
		if (arg->pipe_out == 0)
		{
			arg->save_fd_read = dup(0);
			fd_replacement(arg->fd_read, 0);
			fd_replacement(arg->save_fd_write, 1);
			close(arg->fd_read);
			close(arg->save_fd_write);
		}
	}
	return (0);
}

int	do_redir_out(t_main *arg)
{
	arg->save_fd_write = dup(1);
	ft_printf("FD red_out = %d\n", arg->red_out);
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

pid_t	fork_builtins(char **argv, t_vector *envp, int flag)
{
	int		stat;
	pid_t	pid;

	pid = 0;
	stat = 123;
	if (flag == 1)
		stat = ft_echo(argv + 1);
	else if (flag == 4)
		stat = ft_export(argv, envp);
	else if (flag == 2)
		stat = ft_cd(argv, envp);
	else if (flag == 3)
		stat = ft_pwd();
	else if (flag == 6)
		stat = ft_env(envp);
	else if (flag == 7)
		exit(0);
	else if (flag == 5)
		stat = ft_unset(argv, envp);
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
	return (FALSE);
}

int			launcher(t_main *arg, t_vector *envp)
{
	char	*str;
	pid_t	ret;
	int		flag;

	ret = -1;
	errno = 0;
	str = NULL;
	flag = builtins(*(arg->argv));
	if (flag == FALSE)
		str = filename_parser(*(arg->argv), envp->mem);
	//errno = 0;
	do_pipe(arg);
	//errno = 0;
	do_redir(arg);
	if (str)
	{
		//errno = 0;
		ret = fork_execve(arg->argv, envp->mem, str);
		free(str);
	}
	else if (flag)
	{
		ret = fork_builtins(arg->argv, envp, flag);
	}
	if (*arg->argv && (ret < 0))
		ft_wprintf("%s", *(arg->argv));
	//errno = 0;
	if (arg->pipe_in || arg->red_in > 0)
	{
		fd_replacement(arg->save_fd_read, 0);
		close(arg->save_fd_read);
	}
	if (arg->red_out > 0)
	{
		fd_replacement(arg->save_fd_write, 1);
		close(arg->save_fd_write);
	}
	return (ret);
}
