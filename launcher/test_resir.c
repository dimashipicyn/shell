#include "./includes/inc.h"

int ft_errors(int code);

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
		stat = execve(path_name, argv, envp);
		//ft_errors(0);
		exit(stat);
	}
	/*else
	{
		waitpid(pid, &stat, 0);
		return (0);
	}*/
	return (pid);
}

int		main(int argc, char **argv, char **envp)
{
	int	fd;
	int	stat;
	char	*file;
	pid_t	pid;

	errno = 0;	
	file = "test";
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND | O_TRUNC,
										S_IRWXU | S_IRWXG | S_IRWXO);
	dup2(fd, 0);	
	write(0, "hello", 5);
	pid = fork_execve(argv + 1, envp, argv[1]);
	waitpid(pid, &stat, 0);
	printf("errno = %d\n", errno);
	errno = stat;
	printf("%s \n", strerror(errno));
	printf("status = %d\n", stat);
	return (0);
}