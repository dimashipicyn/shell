/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filepath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:44:05 by tphung            #+#    #+#             */
/*   Updated: 2021/06/16 16:45:46 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"
#include "structs.h"
#include "utils.h"

int	check_exist(char **path, char *file)
{
	int				i;
	DIR				*papka;
	struct dirent	*example;

	i = 0;
	while (path[i])
	{
		papka = opendir(path[i]);
		while (papka)
		{
			example = readdir(papka);
			if (!example)
				break ;
			if (ft_strcmp(example->d_name, file) == 0)
			{
				closedir(papka);
				return (i);
			}
		}
		if (papka)
			closedir(papka);
		i++;
	}
	return (-1);
}

char	*path_join(char *path_str, char *name)
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

char	*filename_parser(char *filename, char **envp)
{
	int		i;
	char	**path_str;
	char	*str;
	char	delim;

	delim = ':';
	if (!filename)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i++], "PATH=", 5))
			break ;
	}
	str = envp[--i];
	path_str = ft_split(str + 5, delim);
	i = check_exist(path_str, filename);
	if (i < 0)
	{
		ft_free_array_ptr((void **)path_str);
		return (NULL);
	}
	str = path_join(path_str[i], filename);
	ft_free_array_ptr((void **)path_str);
	return (str);
}
