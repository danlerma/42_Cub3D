/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:42:43 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/10/04 16:30:45 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

//TODO texturas
void	init_map(t_map *map, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("Something went wrong opening the file.");
	map->map = (char **)ft_calloc(fd_lines(fd) + 1, sizeof(char *));
	if (map->map == NULL)
		error_exit("Malloc failed.");
	map->nsew = (char **)ft_calloc(4 + 1, sizeof(char *));
	if (map->nsew == NULL)
		error_exit("Malloc failed.");
	close(fd);
}

