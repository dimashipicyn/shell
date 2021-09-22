#ifndef HISTORY_H
# define HISTORY_H
#include "vector.h"

# define HISTORY_PATH ".minishell_history.txt"

typedef struct s_history
{
	t_list	*list;
	size_t	size;
	size_t	head;
}	t_history;

t_history	*new_history(void);
Vector(char)	*history_next_entry(t_history *history);
Vector(char)	*history_prev_entry(t_history *history);
Vector(char)	*history_get_entry(t_history *history);
void		history_push_front(t_history *history, Vector(char) *v);
void		history_push_back(t_history *history, Vector(char) *v);
void		history_load_in_file(t_history *history, char *filename);
void		history_save_to_file(t_history *history, char *filename);
void		history_add(t_history *history, Vector(char) *entry);

#endif
