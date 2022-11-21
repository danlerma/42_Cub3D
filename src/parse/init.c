/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:42:43 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/11/21 17:30:23 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init(t_map *map, t_parse *parse, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("Something went wrong opening the file.");
	close(fd);
	map->nsew = (char **)ft_calloc(4 + 1, sizeof(char *));
	if (map->nsew == NULL)
		error_exit("Malloc failed.");
	map->nsew[0] = NULL;
	map->nsew[1] = NULL;
	map->nsew[2] = NULL;
	map->nsew[3] = NULL;
	map->floor = FLOOR;
	map->sky = SKY;
	map->map = NULL;
	parse->init_map = -1;
	parse->pj = 0;
	parse->num_map = 0;
	parse->pos_map = 0;
	parse->frst_chr = 0;
}

void	init_map(t_map *map, t_parse *parse, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '1' || line[i] == '0')
		{
			map->map[parse->pos_map] = (char *) ft_calloc(parse->max_len + 1,
					sizeof(char));
			ft_memset(map->map[parse->pos_map], ' ', parse->max_len - 1);
			ft_memcpy(map->map[parse->pos_map], line,
				count_last_char(line, '1'));
			parse->pos_map++;
			break ;
		}
		else
			error_exit("Wrong map line.");
	}
}
