/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:23:18 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/11/03 17:09:17 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<cub3d.h>
//caracter de en la posicion exacta antes , el caracter
//tengo ue comprobar arriba y abajo

void	collapse(char this, char up, char down, char next)
{
	// if ()
	printf(RED"%c(%d)    %c(%d)    %c(%d)    %c(%d)\n"RESET, this, this, up, up, down,down, next,next);
	if (this == '0' && (next != '1' && next != '0'))
		error_exit("Map is not closed.");
	if (this == '0' && (up != '1' && up != '0'))
		error_exit("Map is not closed.");
	if (this == '0' && (down != '1' && down != '0'))
		error_exit("Map is not closed.");
}

// void	position()

static void	loop_middle_rows(t_parse *parse, char *row, char *prev, char *next)
{
	int	start;
	int	i;

	i = 0;
	start = 0;
	while (row[i])
	{
		if (row[i] == ' ' && parse->frst_chr == 0)
			i++;
		else
		{
			if (parse->frst_chr == 0)
				parse->frst_chr = i;
			collapse(row[i], prev[i], next[i], row[i + 1]);
			i++;
		}
	}
}

static void	loop_frst_lst_rows(char *row)
{
	int	i;

	i = 0;
	while (row[i])
	{
		if (row[i] == ' ')
			i++;
		else if (row[i] != '1' && row[i] != ' ')
			error_exit("Invalid character in a wall.");
		i++;
	}
}

void	check_map(t_map *map, t_parse *parse)
{
	parse->pos_map = 0;
	while (parse->pos_map < parse->num_map)
	{
		printf(GREEN"LINEA %d\n"RESET, parse->pos_map);
		if (parse->pos_map == 0 || parse->pos_map == parse->num_map - 1)
			loop_frst_lst_rows(map->map[parse->pos_map]);
		else
			loop_middle_rows(parse, map->map[parse->pos_map],
				map->map[parse->pos_map - 1], map->map[parse->pos_map + 1]);
		parse->frst_chr = 0;
		parse->pos_map++;
	}
}
