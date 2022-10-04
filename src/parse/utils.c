#include <cub3d.h>

void	free_map(t_map **map)
{
	free(ft_free_malloc((*map)->map));
	free(ft_free_malloc((*map)->nsew));
	free(*map);
}

void	error_exit(char *msg)
{
	printf("Error\n%s\n", msg);
	exit(1);
}
