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

typedef struct s_parse
{
	int	num_map;
}t_parse;

// checkmap.c
t_map	check_map(char *file);

//check_file.c
void	check_file(char *file, t_map *map);

//init.c
void	init_map(t_map *map, char *file);
// void	init_parse(t_parse *parse);

//utils.c
void	error_exit(char *msg);
void	free_map(t_map *map);
size_t	fd_lines(int fd);
void	show_map(t_map *map);

#endif
