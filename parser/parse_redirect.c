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

static Vector(char)	*get_operator(Iterator(char) *iterExpr)
{
	char		    sym;
    Vector(char)	*op;

	op = new(Vector(char));
	if (!op)
		ft_eprintf("get_operator");
	while (m_has_next(iterExpr)) {
	    if (m_next(iterExpr) != ' ') {
	        m_prev(iterExpr);
	        break;
	    }
	}
	while (m_has_next(iterExpr))
	{
		sym = m_next(iterExpr);
		if (!ft_strchr("><", sym))
		{
			m_prev(iterExpr);
			break ;
		}
		m_push_back(op, sym);
	}
	return (op);
}

static BOOLEAN	parse_input_to_delimiter(t_sh_data *sh_data,
	char *op, char *delim)
{
    Vector(char)	*entry;
	int			    fd[2];

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
		if (!ft_strcmp(delim, entry->mem)) {
		    delete(entry);
		    break ;
		}
		write(fd[1], entry->mem, entry->size);
		write(fd[1], "\n", 1);
		delete(entry);
	}
	close(fd[1]);
	sh_data->exec_params.red_in = fd[0];
	return (TRUE);
}

BOOLEAN	parse_redirects(t_sh_data *sh_data, Iterator(char) *iterExpr)
{
    Vector(char)	    *operator;
    Vector(char)	    *operand;
    Vector(void_ptr_t)	*tokens;
	BOOLEAN		        is_open;

	is_open = TRUE;
	tokens = new(Vector(void_ptr_t));
	if (!tokens)
		ft_eprintf("malloc parse_redirects");
	operator = get_operator(iterExpr);
	while (m_has_next(iterExpr) && operator->size && is_open)
	{
		operand = get_token(iterExpr, tokens, sh_data);
		if (tokens->size != 0)
			ft_wprintf("ambiguous redirect");
		is_open = open_file(sh_data, operator->mem, operand->mem);
		is_open = parse_input_to_delimiter(sh_data,
				operator->mem, operand->mem);
		delete(operator);
		delete(operand);
		operator = get_operator(iterExpr);
	}
	delete(operator);
	delete(tokens);
	return (is_open);
}
