/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:19:22 by pdel-pin          #+#    #+#             */
/*   Updated: 2023/05/25 13:19:23 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	close_window(t_play *game)
{
	mlx_destroy_image(game->mlx, game->background.img);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

int	k_pressed(int key, t_play *game)
{
	if (key == KEY_ESC)
		close_window(game);
	else if (key == KEY_W)
		game->player.keys.w = 1;
	else if (key == KEY_A)
		game->player.keys.a = 1;
	else if (key == KEY_S)
		game->player.keys.s = 1;
	else if (key == KEY_D)
		game->player.keys.d = 1;
	else if (key == KEY_LEFT)
		game->player.keys.left = 1;
	else if (key == KEY_RIGHT)
		game->player.keys.right = 1;
	return (0);
}

int	k_released(int key, t_play *game)
{
	if (key == KEY_W)
		game->player.keys.w = 0;
	else if (key == KEY_A)
		game->player.keys.a = 0;
	else if (key == KEY_S)
		game->player.keys.s = 0;
	else if (key == KEY_D)
		game->player.keys.d = 0;
	else if (key == KEY_LEFT)
		game->player.keys.left = 0;
	else if (key == KEY_RIGHT)
		game->player.keys.right = 0;
	return (0);
}
