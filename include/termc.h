#ifndef TERMC_H
# define TERMC_H
# include <sys/ioctl.h>
# include <term.h>

void	reset_input_mode(void);
void	set_input_mode(void);
void	command(char *s, int x, int y);
BOOLEAN	init_term(void);
int		is_empty_stdin(void);
int		get_term_size(void);

#endif
