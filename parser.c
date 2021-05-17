#include "libft.h"
#include "minishell.h"

static void	parse_single_quotes(t_vector *expression, t_vector *token)
{
	char		*ch;

	while (has_next(expression))
	{
		ch = next(expression);
		if (*ch == '\'')
			break ;
		token->method->push_back(token, ch);
	}
}

static void	parse_double_quotes(t_vector *expression,
		t_vector *token, t_vector *envp)
{
	char		sym;
	char		prev_sym;

	sym = 0;
	while (has_next(expression))
	{
		prev_sym = sym;
		sym = *(char *)next(expression);
		if (sym == '"' && prev_sym !='\\')
			break ;
		else if (sym == '$' && prev_sym !='\\')
			parse_env_variable(expression, token, envp);
		else if (sym != '\\' || prev_sym == '\\')
		{
			token->method->push_back(token, &sym);
			sym = 0;
		}
	}
}

void	skip_delimeter(t_vector *vector)
{

}

size_t		ft_ptrlen(const void **ptr)
{
	const void	**ptr_copy;

	ptr_copy = ptr;
	while (*ptr_copy)
		ptr_copy++;
	return (ptr_copy - ptr);
}

static t_vector	*get_token(t_vector *expression, t_vector *tokens, t_vector *envp)
{
	t_vector	*token;
	char		sym;
	char		prev_sym;

	token = new_vector(CHAR);
	prev_sym = 0;
	while (has_next(expression))
	{
		sym = *(char *)next(expression);
		if (sym == '\'' && prev_sym !='\\')
			parse_single_quotes(expression, token);
		else if (sym == '"' && prev_sym !='\\')
			parse_double_quotes(expression, token, envp);
		else if (sym == '$' && prev_sym !='\\')
			parse_env_variable(expression, token, envp);
		else if (ft_strchr(" ", sym))
			break ;
		else if (sym != '\\' || prev_sym == '\\')
			token->method->push_back(token, &sym);
		prev_sym = sym;
	}
	return (token);
}

void	parse_expression(t_vector *expression, t_vector *envp)
{
	t_vector	*tokens;
	t_vector	*token;

	tokens = new_vector(PTR);
	while (has_next(expression))
	{
		token = get_token(expression, tokens, envp);
		tokens->method->push_back(tokens, &token);
	}
	t_vector	**t;
	while (has_next(tokens))
	{
		t = next(tokens);
		ft_putendl_fd((*t)->mem, 1);
	}
}
