/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:06:28 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/11/15 14:00:16 by dlerma-c         ###   ########.fr       */
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
# define VALID "10NSEW"

typedef struct s_parse
{
	int	init_map; //posicion donde empieza el mapa
	int	num_map; //cantidad de lineas de mapa
	int	pos_map; //posicion para guardar el mapa linea a linea
	int	frst_chr; //primer caracter no espacio
	int	pj; //posicion de personaje (NSWE)
	int	max_len; //maxima longitud de la linea mayor
}t_parse;

//check_file.c
t_map	check_file(char *file);

//check_map.c
void	check_map(t_map *map, t_parse *parse);

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
