#include <fcntl.h>
#include "libft.h"
#include "history.h"

t_history	*new_history(void)
{
	t_history	*new;

	new = ft_calloc(1, sizeof(t_history));
	if (!new)
		ft_eprintf("");
	return (new);
}

void	history_load_in_file(t_history *history, char *filename)
{
	int			fd;
	char		*line;
	t_vector	*new_entry;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_eprintf("can't open %s", filename);
	while (get_next_line(fd, &line) > 0)
	{
		new_entry = new_vector(CHAR);
		if (!line || !new_entry)
			ft_eprintf("");
		new_entry->method->load(new_entry, line, ft_strlen(line));
		free(line);
		history_push_back(history, new_entry);
	}
	new_entry = new_vector(CHAR);
	if (!line || !new_entry)
		ft_eprintf("");
	new_entry->method->load(new_entry, line, ft_strlen(line));
	free(line);
	history_push_back(history, new_entry);
	close(fd);
}

void	history_save_to_file(t_history *history, char *filename)
{
	int			fd;
	t_list		*list;
	t_vector	*entry;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd < 0)
		ft_eprintf("can't open %s", filename);
	list = history->list;
	while (list)
	{
		entry = (t_vector *)list->content;
		write(fd, entry->mem, entry->size);
		list = list->next;
		if (list)
			write(fd, "\n", 1);
	}
}
