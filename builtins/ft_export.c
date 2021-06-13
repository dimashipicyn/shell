/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:15:36 by tphung            #+#    #+#             */
/*   Updated: 2021/06/13 15:52:14 by lbespin          ###   ########.fr       */
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
		//printf("POS in ENVP = %d\n", envp->pos);
		var_env = *(char**)next(envp);
		equal = ft_strchr(var_env, '=') - var_env; 
		if (ft_strncmp(var_env, var, equal) == 0)
		{
			//printf("FOUND in ENVP = %s\n", var_env);
			return (envp->pos - 1);
		}
		//printf("VAR in ENVP = %s\n", var_env);
	}
	return (pos);
}

int ft_export(char **argv, t_vector *envp)
{
	int	i;
	int	equal;
	int	pos;
	char *str;

	i = 1;
	pos = -1;
	//printf("I AM EXPORT\n");
	while (argv[i])
	{
		equal = ft_strchr(argv[i], '=') - argv[i];
		if (equal > 0)
		{
			str = ft_substr(argv[i], 0, equal);
			printf("STR = %s\n", str);
			pos = locate_env(str, envp);
			//printf("POS = %d\n", pos);
			free(str);
			str = ft_strdup(argv[i]);
			if (pos >= 0)
			{
				free(*(char**)envp->method->at(envp, pos));
				envp->method->erase(envp, pos);
				envp->method->insert(envp, &str, pos);
			}
			else
				envp->method->push_back(envp, &str);
		}
		i++;
	}
	envp->pos = 0;
	while(has_next(envp))
		printf("%s\n", *(char**)next(envp));
	return (0);
}
