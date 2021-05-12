/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:11:22 by tphung            #+#    #+#             */
/*   Updated: 2021/04/12 15:36:31 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int			check_exist(char **path, char *file)
{
	int				i;
	size_t			l_f;
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
				l_f = (size_t)ft_strlen(example->d_name);
				if (ft_strncmp(example->d_name, file, l_f) == 0)
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
	if (!path_name)
		return (0);
	return (path_name);
}

int			fork_execve(char **argv, char **envp, char *path_name)
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
		stat = execve(path_name, argv, envp);
		ft_errors(0);
		exit(stat);
	}
	else
	{
		waitpid(pid, &stat, 0);
		return (0);
	}
	return (0);
}

char	*filename_parser(char *filename, char **envp)
{
	int		i;
	char	**path_str;
	char	*str;
	char	delim;

	i = 0;
	delim = ':';
	if (ft_strchr("./", filename[0]))
		return (filename);
	while(ft_strncmp(envp[i++], "PATH=", 5))
		;
	str = envp[--i];
	path_str = ft_split(str + 5, &delim);
	//printf("%s\n", strerror(errno));
	i = check_exist(path_str, filename);
	//if (i < 0)
	//	printf("%s\n", strerror(errno));
	str = path_join(path_str[i], filename);
	//if (str == 0)
	//	printf("%s\n", strerror(errno));
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
		ft_errors(0);
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
		ft_errors(0);
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
	int	fd;

	if (arg->red_out == 0)
		return (0);
	else if (arg->red_out == 1)
	{
		fd = open(arg->red_name, O_CREAT | O_WRONLY | O_APPEND | O_TRUNC,
											S_IRWXU | S_IRWXG | S_IRWXO);
	}
	else if (arg->red_out == 2)
	{
		fd = open(arg->red_name, O_CREAT | O_WRONLY | O_APPEND,
											S_IRWXU | S_IRWXG | S_IRWXO);
	}
	if (fd < 0)
	{
		ft_errors(0);
		exit(1);
	}
	if (arg->pipe_in == 0)
		arg->save_fd_write = dup(1);
	fd_replacement(fd, 1);
	close(fd);
	return (0);
}

int	do_redir_in(t_main *arg)
{
	int fd;

	if (arg->red_in == 0)
		return (0);
	else if (arg->red_in == 1)
	{
		fd = open(arg->red_name, O_RDONLY,
											S_IRWXU | S_IRWXG | S_IRWXO);
	}
	if (fd < 0)
	{
		ft_errors(0);
		exit(1);
	}
	if (arg->pipe_in != 0)
	{
		arg->pipe_in = 0;
	}
	else
		arg->save_fd_read = dup(0);
	fd_replacement(fd, 0);
	close(fd);
	return (0);
}

int			launcher(t_main *arg)
{
	char	*str;

	errno = 0;
	do_pipe(arg);
	errno = 0;
	do_redir_out(arg);
	errno = 0;
	do_redir_in(arg);
	errno = 0;
	str = filename_parser(*(arg->argv + 1), arg->envp);
	errno = 0;
	fork_execve(arg->argv + 1, arg->envp, str);
	errno = 0;
	if (arg->pipe_in || arg->red_in)
	{
		fd_replacement(arg->save_fd_read, 0);
		close(arg->save_fd_read);
	}
	if (arg->red_out)
	{
		fd_replacement(arg->save_fd_write, 1);
		close(arg->save_fd_write);
	}
	return (0);
}