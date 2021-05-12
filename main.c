#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "term.h"
#include "history.h"
#include "readline.h"

#define PROMPT "\033[32mminishell:> \033[0m"
#define RIGHT_KEY "\E[C"
#define LEFT_KEY "\E[D"
#define UP_KEY "\E[A"
#define DOWN_KEY "\E[B"

void	print_newlines(int len)
{
	int	newlines;
	int	column;

	column = get_term_size();
	newlines = (len + 11) / column;
	while (newlines-- >= 0)
		ft_putendl_fd("", 1);
}

enum operator
{
	PIPE,
	IN,
	OUT,
	APPEND
};

typedef struct s_token
{
	t_vector		*tok;
	enum operator	op;
	int				fd;
}	t_token;

void	parse_single_quotes(t_vector *expression, t_vector *token)
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
void	parse_env_variable(t_vector *expression, t_vector *token, t_vector *envp, char *p)
{
	char *next_env;
	char *s;

	while (has_next(envp))
	{
		next_env = *(char **)next(envp);
		s = ft_strchr(next_env, '=');
		if (!s)
			continue ;
		if (!ft_strncmp(next_env, p + 1, s - next_env))
		{
			s++;
			while (*s)
			{
				next(expression);
				token->method->push_back(token, s);
				s++;
			}
			break ;
		}
	}
}

void	parse_double_quotes(t_vector *expression, t_vector *token, t_vector *envp)
{
	char		*ch;

	while (has_next(expression))
	{
		ch = next(expression);
		if (*ch == '"')
			break ;
		else if (*ch == '$')
			parse_env_variable(expression, token, envp, ch);
		else
			token->method->push_back(token, ch);
	}
}

t_vector *get_token(t_vector *expression, t_vector *envp)
{
	t_vector 	*token;
	char		*ch;

	token = new_vector(CHAR);
	while (has_next(expression))
	{
		ch = next(expression);
		if (*ch == '\'')
			parse_single_quotes(expression, token);
		else if (*ch == '"')
			parse_double_quotes(expression, token, envp);
		else if (ft_strchr(" ", *ch))
			break ;
		else
			token->method->push_back(token, ch);
	}
	return (token);
}

void	lexer(t_vector *expression, t_vector *envp)
{
	t_vector *tokens;
	t_vector *token;

	tokens = new_vector(PTR);
	while (has_next(expression))
	{
		token = get_token(expression, envp);
		tokens->method->push_back(tokens, &token);
	}
	t_vector **t;
	while (has_next(tokens))
	{
		t = next(tokens);
		ft_putendl_fd((*t)->mem, 1);
	}
}

int	main(int argc, const char *argv[], const char **envp)
{
	t_history	*history;
	t_vector	*new_entry;
	t_vector	*envp_clone;

	init_term();
	history = new_history();
	history_load_in_file(history, "test.txt");
	envp_clone = new_vector(PTR);
	int i = 0;
	while (envp[i])
		i++;
	envp_clone->method->load(envp_clone, envp, i);
	set_input_mode();
	ft_putstr_fd(PROMPT, 1);
	while (1)
	{
		new_entry = new_vector(CHAR);
		history_push_front(history, new_entry);
		readline(history);
		print_newlines(new_entry->size);
		lexer(new_entry, envp_clone);
		ft_putstr_fd(PROMPT, 1);
	}
	history_save_to_file(history, "test.txt");
	reset_input_mode();
	return (0);
}
