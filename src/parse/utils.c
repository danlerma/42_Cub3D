/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:08:41 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/10/04 12:08:42 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
}

void	error_exit(char *msg)
{
	printf("Error\n%s\n", msg);
	exit(1);
}
