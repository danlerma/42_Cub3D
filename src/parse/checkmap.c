#include <cub3d.h>

static void	init_map(t_map **map)
{
	*map = (t_map *)ft_calloc(1 + 1, sizeof(t_map));
	if (*map == NULL)
		error_exit("Malloc failed.");
	(*map)->map = (char **)ft_calloc(1 + 1, sizeof(char *));
	if ((*map)->map == NULL)
		error_exit("Malloc failed.");
	//TODO texturas
	(*map)->nsew = (char **)ft_calloc(4 + 1, sizeof(char *));
	if ((*map)->map == NULL)
		error_exit("Malloc failed.");

	(*map)->bot = "220,100,0";
	(*map)->top = "225,30,0";
}

static void	read_map(int fd, t_map **map)
{
	// int		i;

	(*map)->map[0] = get_next_line(fd);
	// i = 0;
	// while (*map->map[i] != NULL)
	// {
	// 	printf(CYAN"%s"RESET, map->map[i]);
	// 	i++;
	// 	*map->map[i] = get_next_line(fd);
	// }
}


t_map	*checkmap(char *file)
{
	t_map	*map;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("Something went wrong opening the file.");
	init_map(&map);
	read_map(fd, &map);
	return (map);
}
