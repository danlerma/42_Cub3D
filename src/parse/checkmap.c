/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:08:29 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/10/04 12:21:02 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

//TODO texturas
static void	init_map(t_map *map, int fd)
{
	map->map = (char **)ft_calloc(fd_lines(fd) + 1, sizeof(char *));
	if (map->map == NULL)
		error_exit("Malloc failed.");
	map->nsew = (char **)ft_calloc(4 + 1, sizeof(char *));
	if (map->nsew == NULL)
		error_exit("Malloc failed.");
	map->floor = "220,100,0";
	map->sky = "225,30,0";
}

static void	read_map(char *file, t_map *map)
{
	int	i;
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("Something went wrong opening the file.");
	map->map[0] = get_next_line(fd);
	i = 0;
	while (map->map[i] != NULL)
	{
		printf("%s", map->map[i]);
		map->map[++i] = get_next_line(fd);
	}
	printf("\n");
	close(fd);
}

t_map	check_map(char *file)
{
	t_map	map;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("Something went wrong opening the file.");
	init_map(&map, fd);
	close(fd);
	read_map(file, &map);
	return (map);
}
