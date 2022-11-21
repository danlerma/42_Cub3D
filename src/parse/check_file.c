/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:08:29 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/11/21 15:14:55 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static char	*assing_walls(char *line)
{
	char	**split;
	char	*aux;

	split = ft_split(line, ' ');
	if (ft_strchr(split[1], '\n'))
		aux = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
	else
		aux = ft_strdup(split[1]);
	check_textures(aux, split[0], split[2]);
	ft_free_malloc(split);
	return (aux);
}

static int	assing_colors(char *line)
{
	char	**split;
	char	*aux;

	split = ft_split(line, ' ');
	if (ft_strchr(split[1], '\n'))
		aux = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
	else
		aux = ft_strdup(split[1]);
	check_colors(aux, split[0], split[2]);
	ft_free_malloc(split);
	free(aux);
	return (0);
}

static int	identify_firs_char(char *line, t_map *map, int i)
{
	if (line[i] == 'F')
		map->floor = assing_colors(line);
	else if (line[i] == 'C')
		map->sky = assing_colors(line);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		map->nsew[0] = assing_walls(line);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		map->nsew[1] = assing_walls(line);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		map->nsew[2] = assing_walls(line);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		map->nsew[3] = assing_walls(line);
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
		else if (identify_firs_char(line, map, i) == 0)
			break ;
	}
}
//PROBLEMAS DE LONGITUD EN FIRST_LAST
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
	return (map);
}
