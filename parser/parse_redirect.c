#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "termc.h"
#include "readline.h"

static BOOLEAN	reopen_file(char *filename, int flags, mode_t mode, int *fd)
{
	close(*fd);
	errno = 0;
	*fd = open(filename, flags, mode);
	if (*fd < 0)
		return (FALSE);
	return (TRUE);
}

static BOOLEAN	open_file(t_sh_data *sh_data, char *op, char *filename)
{
	BOOLEAN	is_open;

	is_open = TRUE;
	if (!ft_strcmp(op, ">>"))
		is_open = reopen_file(filename, O_APPEND | O_WRONLY | O_CREAT,
				0644, &(sh_data->exec_params.red_out));
	else if (!ft_strcmp(op, ">"))
		is_open = reopen_file(filename, O_WRONLY | O_CREAT | O_TRUNC,
				0644, &(sh_data->exec_params.red_out));
	else if (!ft_strcmp(op, "<"))
		is_open = reopen_file(filename, O_RDONLY,
				0644, &(sh_data->exec_params.red_in));
	if (errno)
		ft_wprintf("can't open file %s", filename);
	errno = 0;
	return (is_open);
}

static t_vector	*get_operator(t_vector *expression)
{
	char		sym;
	t_vector	*token;

	token = new_vector(CHAR);
	if (!token)
		ft_eprintf("malloc token");
	skip_delimiters(expression, " ");
	while (has_next(expression))
	{
		sym = *(char *)next(expression);
		if (!ft_strchr("><", sym))
		{
			previous(expression);
			break ;
		}
		token->method->push_back(token, &sym);
	}
	return (token);
}

static BOOLEAN	parse_input_to_delimiter(t_sh_data *sh_data,
	char *op, char *delim)
{
	t_vector	*entry;
	int			fd[2];

	if (ft_strcmp(op, "<<") != 0)
		return (TRUE);
	if (pipe(fd) == -1)
		return (FALSE);
	while (TRUE)
	{
		ft_putstr_fd("> ", 2);
		set_input_mode();
		entry = readline(sh_data->history);
		reset_input_mode();
		ft_putendl_fd("", 2);
		if (!ft_strcmp(delim, entry->mem))
			break ;
		write(fd[1], entry->mem, entry->size);
		write(fd[1], "\n", 1);
		delete(entry);
	}
	delete(entry);
	close(fd[1]);
	sh_data->exec_params.red_in = fd[0];
	return (TRUE);
}

BOOLEAN	parse_redirects(t_sh_data *sh_data, t_vector *expression)
{
	t_vector	*operator;
	t_vector	*operand;
	t_vector	*tokens;
	BOOLEAN		is_open;

	is_open = TRUE;
	tokens = new_vector(PTR);
	if (!tokens)
		ft_eprintf("malloc parse_redirects");
	operator = get_operator(expression);
	while (has_next(expression) && operator->size && is_open)
	{
		operand = get_token(expression, tokens, sh_data);
		if (tokens->size != 0)
			ft_wprintf("ambiguous redirect");
		is_open = open_file(sh_data, operator->mem, operand->mem);
		is_open = parse_input_to_delimiter(sh_data,
				operator->mem, operand->mem);
		delete(operator);
		delete(operand);
		operator = get_operator(expression);
	}
	delete(operator);
	delete(tokens);
	return (is_open);
}
