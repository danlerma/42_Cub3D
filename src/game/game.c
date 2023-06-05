/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:19:26 by pdel-pin          #+#    #+#             */
/*   Updated: 2023/06/05 17:58:28 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	do_walls(t_play *game)
{
	t_rayc	ray;
	int		num_frame;

	game->raycast = init_draw(game);
	num_frame = 0;
	while (num_frame < WIN_WIDTH)
	{
		ray = init_ray(game, num_frame);
		check_collision(game, &ray);
		get_frame_height(game, &ray);
		draw_texture(game, &ray, num_frame);
		num_frame++;
	}
}

static int	play_game(t_play *game)
{
	// draw_background(game->background, game->map->floor, game->map->sky);
	check_view(game);
	do_walls(game);
	draw_tdmap(game, game->tdmap, game->map, game->player);
	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->raycast.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->tdmap.img,
		WIN_WIDTH - 10 - game->tdmap.width, 10);
	return (0);
}

void	do_game(t_map *map, t_play *game)
{
	init_game(game, map);
	mlx_loop_hook(game->mlx, play_game, game);
	mlx_hook(game->win, 2, 1L << 0, k_pressed, game);
	mlx_hook(game->win, 3, 1L << 1, k_released, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop(game->mlx);
}
