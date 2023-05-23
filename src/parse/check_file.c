/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:08:29 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/11/22 16:20:09 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	identify_firs_char(char *line, t_map *map, t_parse *parse, int i)
{
	if (line[i] == 'F')
	{
		map->floor = assing_colors(line, parse, parse->check[4]);
		parse->check[4] = -1;
	}
	else if (line[i] == 'C')
	{
		map->sky = assing_colors(line, parse, parse->check[5]);
		parse->check[5] = -1;
	}
	else if (line[i] == 'N' && line[i + 1] == 'O')
	{
		map->nsew[0] = assing_walls(line, parse->check[0]);
		parse->check[0] = -1;
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		map->nsew[1] = assing_walls(line, parse->check[1]);
		parse->check[1] = -1;
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		map->nsew[2] = assing_walls(line, parse->check[2]);
		parse->check[2] = -1;
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		map->nsew[3] = assing_walls(line, parse->check[3]);
		parse->check[3] = -1;
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
			parse->max_len = count_last_char(line, '1');
			break ;
		}
		else if (identify_firs_char(line, map, parse, i) == 0)
			break ;
	}
}

static void	read_file(t_parse *parse, t_map *map, int fd)
{
	int		i;
	char	*line;

	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		i++;
		if (parse->num_map == 0)
			identify_line(line, map, parse, i);
		else
		{
			if (count_last_char(line, '1') > parse->max_len)
				parse->max_len = count_last_char(line, '1');
			parse->num_map++;
		}
		if (ft_strrchr(line, '\n') == NULL)
			parse->max_len++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

t_map	check_file(char *file)
{
	t_map	map;
	t_parse	parse;
	char	*point;
	int		fd;

	point = ft_strchr(file, '.');
	if (point == NULL || ft_strncmp(point, ".cub", ft_strlen(file)) != 0)
		error_exit("Invalid format.");
	init(&map, &parse, file);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("Something went wrong opening the file.");
	read_file(&parse, &map, fd);
	close(fd);
	if (parse.init_map != -1)
		save_map(&map, &parse, file);
	save_other_data(&map);
	check_map(&map, &parse);
	free(parse.color);
	free(parse.hex);
	return (map);
}
