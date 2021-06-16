#ifndef UTILS_H
# define UTILS_H

char	*filename_parser(char *filename, char **envp);
pid_t	launcher(t_main *arg, t_vector *envp);
int		locate_env(char *var, t_vector *envp);
int		fd_replacement(int old_fd, int new_fd);
int		ft_cd(char **args, t_vector *envp);
int		ft_pwd(void);
int		ft_export(char **argv, t_vector *envp);
int		ft_env(t_vector *envp);
int		ft_echo(char **args);
int		ft_unset(char **argv, t_vector *envp);

#endif
