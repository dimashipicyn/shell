/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:15:36 by tphung            #+#    #+#             */
/*   Updated: 2021/06/17 15:05:28 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

int	locate_env(char *var, t_vector *envp)
{
	int		pos;
	int		equal;
	char	*var_env;

	pos = -1;
	envp->pos = 0;
	while (has_next(envp))
	{
		var_env = *(char **)next(envp);
		equal = ft_strchr(var_env, '=') - var_env;
		if (ft_strncmp(var_env, var, equal) == 0)
		{
			return (envp->pos - 1);
		}
	}
	return (pos);
}

char	*choose_name(char *full_var)
{
	int		equal;
	char	*arr;
	char	*str;

	arr = ft_strchr(full_var, '=');
	if (arr > 0)
	{
		equal = arr - full_var;
		str = ft_substr(full_var, 0, equal);
	}
	else
		str = ft_strdup(full_var);
	return (str);
}

int	export_in_vector(t_vector *envp, char *str, int pos)
{
	if (pos >= 0 && ft_strchr(str, '=') > 0)
	{
		free(*(char **)envp->method->at(envp, pos));
		envp->method->erase(envp, pos);
		envp->method->insert(envp, &str, pos);
	}
	else if (pos < 0)
		envp->method->push_back(envp, &str);
	else
		free(str);
	return (0);
}

int	print_export(t_vector *envp)
{
	char	*var_env;
	char	*equal;

	envp->pos = 0;
	while (has_next(envp))
	{
		write(1, "declare -x ", 11);
		var_env = *(char **)next(envp);
		equal = ft_strchr(var_env, '=');
		if (equal == NULL)
			ft_printf("%s", var_env);
		else
			ft_printf("%.*s\"%s\"", equal - var_env + 1, var_env, equal + 1);
		write(1, "\n", 1);
	}
	envp->pos = 0;
	return (0);
}

int	ft_export(char **argv, t_vector *envp)
{
	int		i;
	int		pos;
	char	*str;

	i = 1;
	while (argv[i])
	{
		pos = -1;
		str = choose_name(argv[i]);
		pos = locate_env(str, envp);
		free(str);
		str = ft_strdup(argv[i]);
		export_in_vector(envp, str, pos);
		i++;
	}
	if (!argv[1])
		print_export(envp);
	return (0);
}
