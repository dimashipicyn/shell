#include "libft.h"
#include "history.h"
#include "term.h"

#define RIGHT_KEY "\E[C"
#define LEFT_KEY "\E[D"
#define UP_KEY "\E[A"
#define DOWN_KEY "\E[B"

void	move_left(int n)
{
	if (n > 0)
		command("LE", n, 0);
}

void	navigation(t_vector *buf, t_history *history, char *escape, int *cursor)
{
	t_vector	*entry;
	t_vector	*old_entry;

	old_entry = history_get_entry(history);
	if (!ft_strcmp(escape, DOWN_KEY))
	{
		entry = history_prev_entry(history);
		old_entry->method->load(old_entry, buf->mem, buf->size);
		buf->method->load(buf, entry->mem, entry->size);
		*cursor = entry->size;
	}
	if (!ft_strcmp(escape, UP_KEY))
	{
		entry = history_next_entry(history);
		old_entry->method->load(old_entry, buf->mem, buf->size);
		buf->method->load(buf, entry->mem, entry->size);
		*cursor = entry->size;
	}
	if (!ft_strcmp(escape, LEFT_KEY) && *cursor > 0)
		*cursor -= 1;
	if (!ft_strcmp(escape, RIGHT_KEY) && *cursor < (int)buf->size)
		*cursor += 1;
}
