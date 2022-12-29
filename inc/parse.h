/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:06:28 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/12/29 17:06:33 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H

# define PARSE_H

# define FLOOR 1295376
# define SKY 4431833
# define NO "./img/wall_north.xpm"
# define SO "./img/wall_south.xpm"
# define EA "./img/wall_east.xpm"
# define WE "./img/wall_west.xpm"
# define VALID "10NSEW"

typedef struct s_parse
{
	int	init_map;
	int	num_map;
	int	pos_map;
	int	frst_chr;
	int	pj;
	int	max_len;
}t_parse;

//check_file.c
t_map	check_file(char *file);

//check_map.c
void	check_map(t_map *map, t_parse *parse);

//check_img.c
void	check_textures(char *texture, char *name, char *check);
void	check_colors(char *color, char *name, char *check);

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
