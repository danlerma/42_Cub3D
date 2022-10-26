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

static void	save_map(t_map *map, t_parse *parse, char *file)
{
	int		fd;
	int		i;
	int		pos;
	char	*line;

	map->map = (char **)ft_calloc(parse->num_map + 1, sizeof(char *));
	if (map->map == NULL)
		error_exit("Malloc failed.");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("Something went wrong opening the file.");
	line = get_next_line(fd);
	i = 0;
	pos = 0;
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

static int	identify_firs_char(char *line, t_map *map, int i)
{
	if (line[i] == 'F')
	{
		free(map->floor);
		map->floor = ft_strdup(line);
	}
	else if (line[i] == 'C')
	{
		free(map->sky);
		map->sky = ft_strdup(line);
	}
	else if (line[i] == 'N' && line[i + 1] == 'O')
	{
		free(map->nsew[0]);
		map->nsew[0] = ft_strdup(line);
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		free(map->nsew[1]);
		map->nsew[1] = ft_strdup(line);
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		free(map->nsew[2]);
		map->nsew[2] = ft_strdup(line);
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		free(map->nsew[3]);
		map->nsew[3] = ft_strdup(line);
	}
	else
		error_exit("Wrong map.");
	return (0);
}

static void	identify_line(char *line, t_map *map, t_parse *parse, int num)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n')
			i++;
		else if (line[i] == '1' || line[i] == '0')
		{
			parse->init_map = num;
			parse->num_map++;
			break ;
		}
		else if (identify_firs_char(line, map, i) == 0)
			break ;
	}
}

static void	read_file(char *file, t_parse *parse, t_map *map)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("Something went wrong opening the file.");
	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		i++;
		if (parse->num_map == 0)
			identify_line(line, map, parse, i);
		else
			parse->num_map++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

t_map	check_map(char *file)
{
	t_map	map;
	t_parse	parse;
	char	*point;

	point = ft_strchr(file, '.');
	if (point == NULL || ft_strncmp(point, ".cub", ft_strlen(file)) != 0)
		error_exit("Invalid format.\n");
	init(&map, &parse, file);
	read_file(file, &parse, &map);
	save_map(&map, &parse, file);
	return (map);
}
