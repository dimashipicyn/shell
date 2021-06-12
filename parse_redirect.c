#include "libft.h"
#include "minishell.h"
#include "parser.h"

BOOLEAN	reopen_file(char *filename, int flags, mode_t mode, int *fd)
{
	close(*fd);
	errno = 0;
	*fd = open(filename, flags, mode);
	if (*fd < 0)
		return (FALSE);
	return (TRUE);
}

BOOLEAN	open_file(t_sh_data *sh_data, char *op, char *filename)
{
	BOOLEAN	is_open;

	is_open = TRUE;
	if (!ft_strcmp(op, ">>"))
		is_open = reopen_file(filename, O_APPEND | O_CREAT, 0644, &(sh_data->exec_params.red_out));
	else if (!ft_strcmp(op, ">"))
		is_open = reopen_file(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644, &(sh_data->exec_params.red_out));
	else if (!ft_strcmp(op, "<"))
		is_open = reopen_file(filename, O_RDONLY, 0644, &(sh_data->exec_params.red_in));
	if (errno)
		ft_wprintf("can't open file %s", filename);
	errno = 0;
	return (is_open);
}

t_vector	*get_operator(t_vector *expression)
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
	while (has_next(expression))
	{
		operator = get_operator(expression);
		if (operator->size == 0 || !is_open)
		{
			delete(operator);
			break ;
		}
		operand = get_token(expression, tokens, sh_data);
		if (tokens->size != 0)
			ft_wprintf("ambiguous redirect");
		is_open = open_file(sh_data, operator->mem, operand->mem);
		delete(operator);
		delete(operand);
	}
	delete(tokens);
	return (is_open);
}
