/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:08:41 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/11/03 15:54:15 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	show_map(t_map *map)
{
	int	i;

	i = 0;
	printf(CYAN"------------ NSEW ------------\n"RESET);
	printf("map->nsew[0]-> %s\n", map->nsew[0]);
	printf("map->nsew[1]-> %s\n", map->nsew[1]);
	printf("map->nsew[2]-> %s\n", map->nsew[2]);
	printf("map->nsew[3]-> %s\n", map->nsew[3]);
	printf(CYAN"------------ F & C ------------\n"RESET);
	printf("map->floor -> %s\n", map->floor);
	printf("map->sky -> %s\n", map->sky);
	printf(CYAN"------------ MAP ------------\n"RESET);
	while (map->map[i])
	{
		printf("%s#\n", map->map[i]);
		i++;
	}

}

size_t	fd_lines(int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (i);
}

void	free_map(t_map *map)
{
	free(ft_free_malloc(map->map));
	free(ft_free_malloc(map->nsew));
	free(map->floor);
	free(map->sky);
}

void	error_exit(char *msg)
{
	printf("Error\n%s\n", msg);
	exit(1);
}
