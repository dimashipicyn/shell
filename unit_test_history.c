#include "libft.h"
#include "vector.h"

int	main(int argc, char **argv)
{
	t_history	*history = new_history();
	t_vector	*v1 = new_vector(CHAR);
	t_vector	*v2 = new_vector(CHAR);
	t_vector	*v3 = new_vector(CHAR);
	v1->method->load(v1, "hello", 5);
	v2->method->load(v2, "world", 5);
	v3->method->load(v3, "bro", 3);
	history_push_front(history, v1);
	history_push_front(history, v2);
	history_push_front(history, v3);
	
	t_vector *p;
	/* Check history_get */
	p = history_get_entry(history);
	TEST_CHECK(ft_memcmp(p->mem, "bro", 3) == 0, "Get entry");
	
	/* Check history_next */
	p = history_next_entry(history);
	TEST_CHECK(ft_memcmp(p->mem, "world", 5) == 0, "Next entry 1");
	p = history_next_entry(history);
	TEST_CHECK(ft_memcmp(p->mem, "hello", 5) == 0, "Next entry 2");
	p = history_next_entry(history);
	TEST_CHECK(ft_memcmp(p->mem, "hello", 3) == 0, "Next entry 3");
	
	
	/* Check history_prev */
	p = history_prev_entry(history);
	TEST_CHECK(ft_memcmp(p->mem, "world", 5) == 0, "Prev entry 1");
	p = history_prev_entry(history);
	TEST_CHECK(ft_memcmp(p->mem, "bro", 3) == 0, "Prev entry 2");
	p = history_prev_entry(history);
	TEST_CHECK(ft_memcmp(p->mem, "bro", 3) == 0, "Prev entry 3");


	/* Check load file */
	t_history *h = new_history();
	history_load_in_file(h, "h.txt");
	
	p = history_get_entry(h);
	TEST_CHECK(ft_memcmp(p->mem, "hello", 5) == 0, "Load hist 1");
	p = history_next_entry(h);
	TEST_CHECK(ft_memcmp(p->mem, "world", 5) == 0, "Load hist 2");
	p = history_next_entry(h);
	TEST_CHECK(ft_memcmp(p->mem, "bro", 3) == 0, "Load hist 3");
	p = history_next_entry(h);
	TEST_CHECK(ft_memcmp(p->mem, "bro", 3) == 0, "Load hist 4");

	/* Check save file */
	history_save_to_file(h, "test.txt");
	int fd = open("test.txt", O_RDONLY);
	char *line;

	TEST_CHECK(fd > 0, "Save hist 1");
	get_next_line(fd, &line);
	TEST_CHECK(ft_memcmp(line, "hello", 5) == 0, "Save hist 2");
	get_next_line(fd, &line);
	TEST_CHECK(ft_memcmp(line, "world", 5) == 0, "Save hist 3");
	get_next_line(fd, &line);
	TEST_CHECK(ft_memcmp(line, "bro", 3) == 0, "Save hist 4");
	line = 0;
	int n = get_next_line(fd, &line);
	TEST_CHECK(n == 0, "Save hist 3");
}
