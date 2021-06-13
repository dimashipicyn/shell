#ifndef TERM_H
# define TERM_H
# include <sys/ioctl.h>
# include <term.h>

void	reset_input_mode(void);
void	set_input_mode(void);
void	command(char *s, int x, int y);
void	init_term(void);
int		is_empty_stdin(void);
int		get_term_size(void);

#endif
