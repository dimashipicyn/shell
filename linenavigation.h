#ifndef LINENAVIGATION_H
# define LINENAVIGATION_H

void	move_left(int n);
void	navigation(t_vector *buf, t_history *history,
			char *escape, int *cursor);

#endif
