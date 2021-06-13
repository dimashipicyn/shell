#ifndef UTILS_H
# define UTILS_H

int ft_errors(int code);

int	ft_cd(char **args, char *root_path);
int	ft_pwd(void);
int ft_export(char **argv, t_vector *envp);
int	ft_env(t_vector *envp);
int	ft_echo(char **args);

#endif
