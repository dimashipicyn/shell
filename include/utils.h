#ifndef UTILS_H
# define UTILS_H

int ft_errors(int code);

int	ft_cd(char **args, t_vector *envp);
int	ft_pwd(void);
int	locate_env(char *var, t_vector *envp);
int ft_export(char **argv, t_vector *envp);
int	ft_env(t_vector *envp);
int	ft_echo(char **args);
int ft_unset(char **argv, t_vector *envp);

#endif
