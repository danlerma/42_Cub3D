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

// void leaks(void)
// {
// 	system("leaks -q cub3D");
// }

int	main(int argc, char **argv)
{
	t_map	map;

	// atexit(leaks);
	if (argc != 2)
		error_exit("Wrong arguments");
	map = check_map(argv[1]);
	game(&map);
	free_map(&map);
	return (0);
}








void	load_files(t_game *g, t_data *data)
{
	g->tex.no.img = mlx_xpm_file_to_image(g->ptr, data->no,
			&g->tex.no.width, &g->tex.no.height);
	g->tex.no.addr = mlx_get_data_addr(g->tex.no.img, &g->tex.no.bpp,
			&g->tex.no.line_len, &g->tex.no.endian);
	g->tex.so.img = mlx_xpm_file_to_image(g->ptr, data->so,
			&g->tex.so.width, &g->tex.so.height);
	g->tex.so.addr = mlx_get_data_addr(g->tex.so.img, &g->tex.so.bpp,
			&g->tex.so.line_len, &g->tex.so.endian);
	g->tex.ea.img = mlx_xpm_file_to_image(g->ptr, data->ea,
			&g->tex.ea.width, &g->tex.ea.height);
	g->tex.ea.addr = mlx_get_data_addr(g->tex.ea.img, &g->tex.ea.bpp,
			&g->tex.ea.line_len, &g->tex.ea.endian);
	g->tex.we.img = mlx_xpm_file_to_image(g->ptr, data->we,
			&g->tex.we.width, &g->tex.we.height);
	g->tex.we.addr = mlx_get_data_addr(g->tex.we.img, &g->tex.we.bpp,
			&g->tex.we.line_len, &g->tex.we.endian);
}