/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:06:28 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/10/04 16:25:04 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H

# define PARSE_H

# define FLOOR "------ 220,100,0 ------"
# define SKY "------ 225,30,0 ------"
# define NO "------ ./ruta_a_la_textura_norte ------"
# define SO "------ ./ruta_a_la_textura_sur ------"
# define EA "------ ./ruta_a_la_textura_este ------"
# define WE "------ ./ruta_a_la_textura_oeste ------"

typedef struct s_parse
{
	int	init_map;
	int	num_map;
	int	pos_map;
}t_parse;

// checkmap.c
t_map	check_map(char *file);

//check_file.c
void	check_file(char *file, t_map *map);

//init.c
void	init(t_map *map, t_parse *parse, char *file);
void	init_map(t_map *map, t_parse *parse, char *line);

//utils.c
void	error_exit(char *msg);
void	free_map(t_map *map);
void	show_map(t_map *map);

//save.c
void	save_other_data(t_map *map);
void	save_map(t_map *map, t_parse *parse, char *file);

#endif
