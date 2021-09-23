#ifndef UTILS_H
# define UTILS_H

void	env_starter(Vector(char_ptr_t) *envp);
char	*filename_parser(char *filename, char **envp);
pid_t	launcher(t_main *arg, Vector(char_ptr_t) *envp);
int		locate_env(char *var, Vector(char_ptr_t) *envp);
int		fd_replacement(int old_fd, int new_fd);
int		ft_cd(char **args, Vector(char_ptr_t) *envp);
int		ft_pwd(void);
int		ft_export(char **argv, Vector(char_ptr_t) *envp);
int		ft_env(Vector(char_ptr_t) *envp);
int		ft_echo(char **args);
int		ft_unset(char **argv, Vector(char_ptr_t) *envp);

#endif
