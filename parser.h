#ifndef PARSER_H
# define PARSER_H

t_vector	*get_token(t_vector *expression, t_vector *tokens, t_sh_data *sh_data);
BOOLEAN		parse_redirects(t_sh_data *sh_data, t_vector *expression);
void		parse_arguments(t_sh_data *sh_data, t_vector *expression);

#endif
