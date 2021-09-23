#include "libft.h"
#include "vector.h"
#include "history.h"

void	history_push_front(t_history *history, Vector(char) *new_entry)
{
	ft_list_push_front(&(history->list), new_entry);
	history->size += 1;
	history->head = 0;
}

void	history_push_back(t_history *history, Vector(char) *new_entry)
{
	ft_list_push_back(&(history->list), new_entry);
	history->size += 1;
	history->head = 0;
}

Vector(char)	*history_next_entry(t_history *history)
{
    Vector(char)	*entry;
	t_list		*list;

	if (history->size == 0)
		return (0);
	if (history->head < history->size - 1)
		history->head += 1;
	list = ft_list_at(history->list, history->head);
	entry = list->content;
	return (entry);
}

Vector(char)	*history_prev_entry(t_history *history)
{
	Vector(char)	*entry;
	t_list		*list;

	if (history->size == 0)
		return (0);
	if (history->head > 0)
		history->head -= 1;
	list = ft_list_at(history->list, history->head);
	entry = list->content;
	return (entry);
}

Vector(char)	*history_get_entry(t_history *history)
{
	t_list	*list;

	list = ft_list_at(history->list, history->head);
	return (list->content);
}
