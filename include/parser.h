#ifndef PARSER_H
# define PARSER_H

# define SINGLEQUOTE '\''
# define DOUBLEQUOTE '"'
# define BACKSLASH '\\'
# define DOLOR '$'

typedef struct s_sh_data	t_sh_data;

t_vector	*get_token(t_vector *expression,
				t_vector *tokens, t_sh_data *sh_data);
BOOLEAN		parse_redirects(t_sh_data *sh_data, t_vector *expression);
void		parse_arguments(t_sh_data *sh_data, t_vector *expression);

#endif
