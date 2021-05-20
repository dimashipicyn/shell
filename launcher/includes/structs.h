#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_main
{
	int			pipe_in;
	int			pipe_out;
	int			red_in;
	int 		red_out;
	int			fd_read;
	int 		fd_write;
	int			save_fd_read;
	int			save_fd_write;
	int			status;
	char 		**argv;
	char		**envp;	//vector **envp
	//vector *(pid_t)pid
}	t_main;

#endif
