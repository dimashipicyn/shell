#include <fcntl.h>
#include "libft.h"
#include "vector.h"
#include "history.h"

/**
 * New history object
 * t_history *new_history(void);
 * 
 *
 */
t_history	*constructor_t_history(void *_self)
{
    Vector(char)    *entry = new(Vector(char));
	t_history       *self = _self;

    history_load_in_file(self, HISTORY_PATH);
    history_push_front(self, entry);
	return (self);
}

/**
 * Loading history
 * void history_load_in_file(t_history *history, char *filename);
 * 
 */
void	history_load_in_file(t_history *history, char *filename)
{
	int		        fd;
	int             not_empty;
	char		    *line;
	Vector(char)	*new_entry;

	fd = open(filename, O_RDONLY | O_CREAT,
			S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd < 0)
		ft_eprintf("can't open %s", filename);
	not_empty = 1;
	while (not_empty)
	{
	    not_empty = get_next_line(fd, &line);
		new_entry = new(Vector(char));
		if (!line || !new_entry)
			ft_eprintf("");
		if (strlen(line) > 0) {
		    m_load(new_entry, line, ft_strlen(line));
		    history_push_back(history, new_entry);
		}
		free(line);
	}
	close(fd);
}

/**
 * Save history
 * void history_save_to_file(t_history *history, char *filename);
 * 
 */
void	history_save_to_file(t_history *history, char *filename)
{
	int			fd;
	t_list		*list;
    Vector(char)	*entry;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd < 0)
		ft_eprintf("can't open %s", filename);
	list = history->list->next;
	while (list)
	{
		entry = (Vector(char) *)list->content;
		write(fd, entry->mem, entry->size);
		write(fd, "\n", 1);
		list = list->next;
	}
}

/**
 * Add entry to history
 * Entry t_vector type, is container
 * 
 */
void	history_add(t_history *history, Vector(char) *entry)
{
	ft_list_push_front(&(history->list->next), entry);
	history->size += 1;
	history->head = 0;
}
