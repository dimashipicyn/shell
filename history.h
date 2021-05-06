#ifndef HISTORY_H
# define HISTORY_H
# include "vector.h"

typedef struct s_history
{
	t_list	*list;
	size_t	size;
	size_t	head;
}	t_history;

t_history	*new_history(void);
t_vector	*history_next_entry(t_history *history);
t_vector	*history_prev_entry(t_history *history);
t_vector	*history_get_entry(t_history *history);
void		history_push_front(t_history *history, t_vector *v);
void		history_push_back(t_history *history, t_vector *v);
void		history_load_in_file(t_history *history, char *filename);
void		history_save_to_file(t_history *history, char *filename);

#endif
