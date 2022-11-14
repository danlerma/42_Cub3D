/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:08:41 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/11/14 14:43:37 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	count_last_char(char *str, char c)
{
	int	i;
	int	len;

	i = 0;

	if (str != NULL)
	{
		len = ft_strlen(str);
		while (len > 0)
		{
			len--;
			if (str[len] == c)
				return (len + 1);
		}
	}
	return (-1);
}

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
	// printf("-_>%d\n", map->map[i][3]);
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
