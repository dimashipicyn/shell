#ifndef READLINE_H
# define READLINE_H

Vector(char)	*readline(t_history *history);
void		interpret_stdin(t_sh_data *sh_data);

#endif
