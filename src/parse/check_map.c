/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:23:18 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/11/01 20:28:24 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<cub3d.h>
//caracter de en la posicion exacta antes , el caracter
//tengo ue comprobar arriba y abajo
//RESCTUCTURAR en dos bucles, dependiendo si es de medio o no, no juntarlos en el mismo
static void	check_positions(char up_char, char this_char, int pos, int start)
{
	printf(RED"UP-> %c (%d)        THIS-> %c (%d)       POS-> %d        START-> %d\n"RESET, up_char, up_char, this_char, this_char, pos, start);
	if (start == pos && this_char != '1')
		error_exit("No es un 1.");
}

static void	loop_blocks(t_parse *parse, char *row, char *prev_row, int frt_lst)
{
	int	start;
	int	i;

	i = 0;
	start = 0;
	while (row[i])
	{
		if (row[i] == ' ' && start == 0)
			i++;
		else
		{
			if (parse->frst_chr == 0)
				parse->frst_chr = i;
			if (frt_lst == 1 && (row[i] != '1' && row[i] != ' '))
				error_exit("Walls are not closed.");
			if (frt_lst == 0)
			{
				check_positions(prev_row[i], row[i], i, parse->frst_chr);
				printf(YELLOW"--------------------------------------------------------\n"RESET);
			}
		} 
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
			loop_blocks(parse, map->map[parse->pos_map], NULL, 1);
		else
			loop_blocks(parse, map->map[parse->pos_map], map->map[parse->pos_map - 1], 0);
		parse->frst_chr = 0;
		parse->pos_map++;
	}
}
