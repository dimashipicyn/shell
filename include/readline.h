#ifndef READLINE_H
# define READLINE_H

t_vector	*readline(t_history *history);
void		interpret_stdin(t_sh_data *sh_data);

#endif
