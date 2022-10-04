/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:08:29 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/10/04 16:32:12 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// static void	read_map(char *file, t_map *map)
// {
// 	int	i;
// 	int	fd;

// 	fd = open(file, O_RDONLY);
// 	if (fd == -1)
// 		error_exit("Something went wrong opening the file.");
// 	map->map[0] = get_next_line(fd);
// 	i = 0;
// 	while (map->map[i] != NULL)
// 	{ 
// 		printf("%s", map->map[i]);
// 		map->map[++i] = get_next_line(fd);
// 	}
// 	printf("\n");
// 	close(fd);
// }

t_map	check_map(char *file)
{
	t_map	map;
	char	*point;

	point = ft_strchr(file, '.');
	if (point == NULL || ft_strncmp(point, ".cub", ft_strlen(file)) != 0)
		error_exit("Invalid format.\n");
	init_map(&map, file);
	check_file(file, &map);
	// read_map(file, &map);
	return (map);
}
