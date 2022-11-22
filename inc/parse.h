/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:06:28 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/11/22 14:41:51 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H

# define PARSE_H

# define FLOOR 1295376
# define SKY 4431833
# define UPPER_HEX "0123456789ABCDEF"
# define NO "./img/wall_north.xpm"
# define SO "./img/wall_south.xpm"
# define EA "./img/wall_east.xpm"
# define WE "./img/wall_west.xpm"
# define VALID "10NSEW"

typedef struct s_parse
{
	int		init_map;
	int		num_map;
	int		pos_map;
	int		frst_chr;
	int		pj;
	int		max_len;
	int		*color;
	char	*hex;
}t_parse;

//check_file.c
t_map	check_file(char *file);

//check_map.c
void	check_map(t_map *map, t_parse *parse);

//check_img.c
int		assing_colors(char *line, t_parse *parse);
char	*assing_walls(char *line);

//to_hex.c
void	transform_numbers(t_parse *parse);

//init.c
void	init(t_map *map, t_parse *parse, char *file);
void	init_map(t_map *map, t_parse *parse, char *line);

//utils.c
void	error_exit(char *msg);
void	free_map(t_map *map);
void	show_map(t_map *map);
int		count_last_char(char *str, char c);

//save.c
void	save_other_data(t_map *map);
void	save_map(t_map *map, t_parse *parse, char *file);

#endif
