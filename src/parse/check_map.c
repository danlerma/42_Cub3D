/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:23:18 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/11/21 17:28:37 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<cub3d.h>
//caracter de en la posicion exacta antes , el caracter
//tengo ue comprobar arriba y abajo

static int	collapse(char this, char up, char down, char next)
{
	if (ft_strchr(&VALID[1], this) != NULL)
	{
		if (ft_strchr(VALID, up) == NULL)
			error_exit("Chars of map are wrong.");
		if (ft_strchr(VALID, down) == NULL)
			error_exit("Chars of map are wrong.");
		if (ft_strchr(VALID, next) == NULL)
			error_exit("Chars of map are wrong.");
		if (ft_strchr(&VALID[2], this) != NULL)
			return (1);
	}
	return (0);
}

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
			if (collapse(row[i], prev[i], next[i], row[i + 1]) == 1)
				parse->pj++;
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
		else if (row[i] != '1' && row[i] != ' ' && row[i] != '\0')
			error_exit("Invalid character in a wall.");
		i++;
	}
}

void	check_map(t_map *map, t_parse *parse)
{
	parse->pos_map = 0;
	while (parse->pos_map < parse->num_map)
	{
		if (parse->pos_map == 0 || parse->pos_map == parse->num_map - 1)
			loop_frst_lst_rows(map->map[parse->pos_map]);
		else
			loop_middle_rows(parse, map->map[parse->pos_map],
				map->map[parse->pos_map - 1], map->map[parse->pos_map + 1]);
		parse->frst_chr = 0;
		parse->pos_map++;
	}
	if (parse->pj > 1 || parse->pj <= 0)
		error_exit("There is a problem with the player position.");
}
