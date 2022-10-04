#ifndef PARSE_H

# define PARSE_H

// checkmap.c
t_map	*checkmap(char *file);

//utils.c
void	error_exit(char *msg);
void	free_map(t_map **map);

#endif
