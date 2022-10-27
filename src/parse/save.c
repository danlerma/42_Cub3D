/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:19:20 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/10/26 12:19:27 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	save_other_data(t_map *map)
{
	if (map->floor == NULL)
		map->floor = ft_strdup(FLOOR);
	if (map->sky == NULL)
		map->sky = ft_strdup(SKY);
	if (map->nsew[0] == NULL)
		map->nsew[0] = ft_strdup(NO);
	if (map->nsew[1] == NULL)
		map->nsew[1] = ft_strdup(SO);
	if (map->nsew[2] == NULL)
		map->nsew[2] = ft_strdup(EA);
	if (map->nsew[3] == NULL)
		map->nsew[3] = ft_strdup(WE);
	if (map->map == NULL)
		error_exit("There is no map.");
}

void	save_map(t_map *map, t_parse *parse, char *file)
{
	int		fd;
	int		i;
	char	*line;

	map->map = (char **)ft_calloc(parse->num_map + 1, sizeof(char *));
	if (map->map == NULL)
		error_exit("Malloc failed.");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("Something went wrong opening the file.");
	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		i++;
		if (i >= parse->init_map)
			init_map(map, parse, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
