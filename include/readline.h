#ifndef READLINE_H
# define READLINE_H

# define PROMPT "\033[32mminishell:> \033[0m"

Vector(char)	*readline(t_history *history);
void		    interpret_stdin(t_sh_data *sh_data);

#endif
