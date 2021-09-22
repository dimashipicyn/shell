#include "libft.h"
#include "history.h"
#include "termc.h"

#define RIGHT_KEY "\E[C"
#define LEFT_KEY "\E[D"
#define UP_KEY "\E[A"
#define DOWN_KEY "\E[B"

void	move_left(int n)
{
	if (n > 0)
		command("LE", n, 0);
}

void	navigation(Vector(char) *buf, t_history *history, char *escape, int *cursor)
{
    Vector(char)	*entry;
    Vector(char)	*old_entry;

	old_entry = history_get_entry(history);
	if (!ft_strcmp(escape, DOWN_KEY))
	{
		entry = history_prev_entry(history);
		m_load(old_entry, buf->mem, buf->size);
		m_load(buf, entry->mem, entry->size);
		*cursor = entry->size;
	}
	if (!ft_strcmp(escape, UP_KEY))
	{
		entry = history_next_entry(history);
		m_load(old_entry, buf->mem, buf->size);
		m_load(buf, entry->mem, entry->size);
		*cursor = entry->size;
	}
	if (!ft_strcmp(escape, LEFT_KEY) && *cursor > 0)
		*cursor -= 1;
	if (!ft_strcmp(escape, RIGHT_KEY) && *cursor < (int)buf->size)
		*cursor += 1;
}
