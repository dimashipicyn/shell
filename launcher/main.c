/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:26:52 by tphung            #+#    #+#             */
/*   Updated: 2021/06/08 20:41:32 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/inc.h"
#include "./includes/structs.h"

int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_cd(char **args, char **root_path);
int		locate_env(char *var, t_vector *envp);

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

int		main(int argc, char **argv, char **envp)
{
	t_vector	*envp_copy;
	char	*str;

	envp_copy = new_vector(sizeof(char*));

	str = ft_strdup("FIRST");
	envp_copy->method->push_back(envp_copy, &str);
	str = ft_strdup("hi=SECOND");
	envp_copy->method->push_back(envp_copy, &str);
	str = "THIRD";
	envp_copy->method->push_back(envp_copy, &str);

	ft_export(argv, envp_copy);

	/*
	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
	ft_cd(argv + 1);

	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
	ft_pwd();
	ft_echo(argv + 1);
	while (*envp_copy)
		printf("%s\n", *envp_copy++);

	stat = 1;
	arg.pipe_in = 0;
	arg.pipe_out = 1;
	arg.red_out = 0;
	arg.red_in = 0;
	arg.red_name = "test";
	arg.argc = argc;
	arg.argv = argv;
	arg.envp = envp;
	pid_one = launcher(&arg);

	arg.pipe_in = 1;
	arg.pipe_out = 0;
	arg.red_out = 0;

	des = malloc(sizeof(char*) * 3);
	des[0] = "cat";
	des[1] = "cat";
	des[2] = "-e";
	des[3] = NULL;
	arg.argv = des;
	pid_two = launcher(&arg);
	arg.pipe_in = 1;
	arg.pipe_out = 1;

	waitpid(pid_one, &(arg->status), 0);
	waitpid(pid_two, &(arg->status), 0);

	des = malloc(sizeof(char*) * 3);
	des[0] = "cat";
	des[1] = "cat";
	des[2] = "-e";
	des[3] = NULL;
	arg.argv = des;
	launcher(&arg);

	arg.pipe_in = 1;
	arg.pipe_out = 1;

	des = malloc(sizeof(char*) * 3);
	des[0] = "grep";
	des[1] = "grep";
	des[2] = "l";
	des[3] = NULL;
	arg.argv = des;
	launcher(&arg);

	arg.pipe_in = 1;
	arg.pipe_out = 0;

	des = malloc(sizeof(char*) * 3);
	des[0] = "grep";
	des[1] = "grep";
	des[2] = "in";
	des[3] = NULL;
	arg.argv = des;
	launcher(&arg);

*/
	return (0);
}
