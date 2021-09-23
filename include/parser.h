#ifndef PARSER_H
# define PARSER_H

# define SINGLEQUOTE '\''
# define DOUBLEQUOTE '"'
# define BACKSLASH '\\'
# define DOLOR '$'

typedef struct s_sh_data	t_sh_data;

Vector(char)	*get_token(Iterator(char) *iterExpr,
                           Vector(void_ptr_t) *tokens, t_sh_data *sh_data);
BOOLEAN		parse_redirects(t_sh_data *sh_data, Iterator(char) *iterExpr);
void		parse_arguments(t_sh_data *sh_data, Iterator(char) *iterExpr);

#endif
