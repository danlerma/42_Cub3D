/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:09:16 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/10/04 12:09:16 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	leaks(void)
{
	system("leaks -q cub3D\n");
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_play	game;

	// atexit(leaks);
	if (argc != 2)
		error_exit("Wrong arguments");
	map = check_file(argv[1]);
	// show_map(&map);
	do_game(&map, &game);
	free_map(&map);
	return (0);
}
