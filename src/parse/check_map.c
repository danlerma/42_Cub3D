/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:23:18 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/11/02 13:30:11 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<cub3d.h>
//caracter de en la posicion exacta antes , el caracter
//tengo ue comprobar arriba y abajo
//RESCTUCTURAR en dos bucles, dependiendo si es de medio o no, no juntarlos en el mismo
// static void	check_positions(char up_char, char this_char, int pos, int start)
// {
// 	printf(RED"UP-> %c (%d)        THIS-> %c (%d)       POS-> %d        START-> %d\n"RESET, up_char, up_char, this_char, this_char, pos, start);
// 	if (start == pos && this_char != '1')
// 		error_exit("No es un 1.");
// }

static void	loop_middle_rows(t_parse *parse, char *row)
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
			printf(RED"ROW char %c   (%d)\n"RESET, row[parse->frst_chr], row[parse->frst_chr]);
			if (row[parse->frst_chr] != '1' && row[ft_strlen(row) - 1] != '1')
				error_exit("Middle walls are not closed.");
			i++;
		} 
	}
}

static void	loop_frst_lst_rows(char *row)
{
	int	i;

	i = 0;
	while(row[i])
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
			loop_middle_rows(parse, map->map[parse->pos_map]);
		parse->frst_chr = 0;
		parse->pos_map++;
	}
}
