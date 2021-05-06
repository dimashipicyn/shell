#ifndef LINENAVIGATION_H
# define LINENAVIGATION_H

void		move_cursor(char *escape, int *cursor, int max);
void		move_left(int n);
t_vector	*move_history(t_history *history, char *escape, int *cursor);

#endif
