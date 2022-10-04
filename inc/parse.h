/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:06:28 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/10/04 12:11:03 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H

# define PARSE_H

// checkmap.c
t_map	check_map(char *file);

//utils.c
void	error_exit(char *msg);
void	free_map(t_map *map);
size_t	fd_lines(int fd);

#endif
