/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:26:52 by tphung            #+#    #+#             */
/*   Updated: 2021/05/13 17:13:01 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/inc.h"
#include "./includes/structs.h"

pid_t	launcher(t_main *arg);

int		main(int argc, char **argv, char **envp)
{
	t_main	arg;
	char	**des;
	pid_t	pid_one;
	pid_t	pid_two;
	int		stat;

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

	waitpid(pid_one, &stat, 0);
	waitpid(pid_two, &stat, 0);
/*
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
