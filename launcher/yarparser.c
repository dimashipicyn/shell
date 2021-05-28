/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yarparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:57:04 by tphung            #+#    #+#             */
/*   Updated: 2021/04/12 18:19:58 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int arg_init(t_main *arg, char **envp)
{
    arg->count = 0;
    arg->pipe_in = 0;
    arg->pipe_out = 0;
    arg->red_in = 0;
    arg->red_out = 0;
    arg->fd_read = 0;
    arg->fd_write = 1;
    arg->save_fd_read = 0;
    arg->save_fd_write = 0;
    arg->argc = 0;
    arg->red_name = NULL;
    arg->argv = NULL;
    arg->envp = envp;
    return (0);
}

int get_argv(t_main *arg, char **args)
{
    
}

int parser(char **args, char **envp)
{
    t_main  arg;

    arg_init(&arg, envp);
    while (get_argv(&arg, args) > 0)
    {
        launcher(&arg);
    }
    return (0);    
}