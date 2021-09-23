#ifndef LINENAVIGATION_H
# define LINENAVIGATION_H

void	move_left(int n);
void	navigation(Vector(char) *buf, t_history *history,
			char *escape, int *cursor);

#endif
