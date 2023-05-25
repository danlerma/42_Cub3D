/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:15:26 by pdel-pin          #+#    #+#             */
/*   Updated: 2023/05/25 18:39:49 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_movement(t_play *game)
{
	double	i;
	double	j;

	modf((double)game->player.next.x, &i);
	modf((double)game->player.next.y, &j);
	if (game->map->map[(int)j][(int)i] != '1')
	{
		game->player.x = game->player.next.x;
		game->player.y = game->player.next.y;
		return (1);
	}
	return (0);
}

void	move_player(int key, t_play *game)
{
	if (key == KEY_W)
	{
		game->player.next.x += game->player.dir.x * SPEED;
		game->player.next.y += game->player.dir.y * SPEED;
	}
	if (key == KEY_A)
	{
		game->player.next.x += game->player.dir.y * SPEED;
		game->player.next.y -= game->player.dir.x * SPEED;
	}
	if (key == KEY_S)
	{
		game->player.next.x -= game->player.dir.x * SPEED;
		game->player.next.y -= game->player.dir.y * SPEED;
	}
	if (key == KEY_D)
	{
		game->player.next.x -= game->player.dir.y * SPEED;
		game->player.next.y += game->player.dir.x * SPEED;
	}
}

void	move_view(int key, t_play *game)
{
	double	start_dir;
	double	start_plane;
	int		dir;

	dir = 1;
	if (key == KEY_LEFT)
		dir = -1;
	start_dir = game->player.dir.x;
	start_plane = game->player.plane.x;
	game->player.dir.x = game->player.dir.x * cos(ROT_ANGLE * dir)
		- game->player.dir.y * sin(ROT_ANGLE * dir);
	game->player.dir.y = start_dir * sin(ROT_ANGLE * dir)
		+ game->player.dir.y * cos(ROT_ANGLE * dir);
	game->player.plane.x = game->player.plane.x * cos(ROT_ANGLE * dir)
		- game->player.plane.y * sin(ROT_ANGLE * dir);
	game->player.plane.y = start_plane * sin(ROT_ANGLE * dir)
		+ game->player.plane.y * cos(ROT_ANGLE * dir);
	game->player.ang += (ROT_ANGLE * dir);
}

void	check_view(t_play *game)
{
	game->player.next.x = game->player.x;
	game->player.next.y = game->player.y;
	if (game->player.keys.left)
		move_view(KEY_LEFT, game);
	if (game->player.keys.right)
		move_view(KEY_RIGHT, game);
	if (game->player.keys.w)
		move_player(KEY_W, game);
	if (game->player.keys.a)
		move_player(KEY_A, game);
	if (game->player.keys.s)
		move_player(KEY_S, game);
	if (game->player.keys.d)
		move_player(KEY_D, game);
	if (check_movement(game))
	{
		game->player.x = game->player.next.x;
		game->player.y = game->player.next.y;
	}
}
