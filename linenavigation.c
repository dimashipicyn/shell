#include "libft.h"
#include "vector.h"
#include "history.h"
#include "term.h"

#define RIGHT_KEY "\E[C"
#define LEFT_KEY "\E[D"
#define UP_KEY "\E[A"
#define DOWN_KEY "\E[B"

void	move_cursor(char *escape, int *cursor, int max)
{
	if (!ft_strcmp(escape, LEFT_KEY) && *cursor > 0)
	{
		*cursor -= 1;
	}
	if (!ft_strcmp(escape, RIGHT_KEY) && *cursor < max)
	{
		*cursor += 1;
	}
}

void	move_left(int n)
{
	if (n > 0)
		command("LE", n, 0);
}

t_vector	*move_history(t_history *history, char *escape, int *cursor)
{
	t_vector	*entry;

	entry = history_get_entry(history);
	if (!ft_strcmp(escape, DOWN_KEY))
	{
		entry = history_prev_entry(history);
		*cursor = entry->size;
	}
	if (!ft_strcmp(escape, UP_KEY))
	{
		entry = history_next_entry(history);
		*cursor = entry->size;
	}
	return (entry);
}
