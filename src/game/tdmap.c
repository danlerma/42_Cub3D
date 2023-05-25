/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tdmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:19:13 by pdel-pin          #+#    #+#             */
/*   Updated: 2023/05/25 18:34:50 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	pixel_put(t_img *img, int i, int j, int color)
{
	char	*dst;

	if (i >= 0 && i < WIN_WIDTH && j >= 0 && j < WIN_HEIGHT)
	{
		dst = img->data_addr + (j * img->size_line + i * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_rays(t_play *game, float tile)
{
	t_coord	coll;
	t_coord	pos;
	float	ang;
	float	point;

	pos.x = tile * game->player.x;
	pos.y = tile * game->player.y;
	point = 1;
	ang = -M_PI / 6;
	while (ang < M_PI / 6)
	{
		point = 0;
		coll.x = pos.x + point * cos(game->player.ang + ang);
		coll.y = pos.y + point * sin(game->player.ang + ang);
		while (game->map->map[(int)((pos.y + (int)coll.y - (int)pos.y) / tile)]
				[(int)((pos.x + (int)coll.x - (int)pos.x) / tile)] != '1')
		{
			coll.x = pos.x + point * cos(game->player.ang + ang);
			coll.y = pos.y + point * sin(game->player.ang + ang);
			point += 0.1;
		}
		ang += ANGLE;
	}
}

void	draw_player(t_play *game, t_img tdmap, t_player player, float tile)
{
	t_coord	iter;
	t_coord	pos;
	int		size;

	iter.y = -1;
	size = 5;
	pos.x = player.x * tile - size / 2;
	pos.y = player.y * tile - size / 2;
	draw_rays(game, tile);
	while (++iter.y < size)
	{
		iter.x = -1;
		while (++iter.x < size)
			pixel_put(&tdmap, iter.x + pos.x, iter.y + pos.y, TDMAP_PLAYER);
	}
}

void	draw_tdmap(t_play *game, t_img tdmap, t_map *map, t_player player)
{
	t_coord	iter;
	float	tile;

	tile = tdmap.width / ft_strlen(map->map[0]);
	iter.y = 0;
	while (iter.y < tdmap.height)
	{
		iter.x = 0;
		while (iter.x < tdmap.width)
		{
			if (map->map[(int)(iter.y / tile)][(int)(iter.x / tile)] == '0')
				pixel_put(&tdmap, iter.x, iter.y, TDMAP_FLOOR);
			else if (map->map[(int)(iter.y / tile)][(int)(iter.x / tile)] == '1'
				|| map->map[(int)(iter.y / tile)][(int)(iter.x / tile)] == 32)
				pixel_put(&tdmap, iter.x, iter.y, TDMAP_WALL);
			else
				pixel_put(&tdmap, iter.x, iter.y, TDMAP_FLOOR);
			iter.x++;
		}
		iter.y++;
	}
	draw_player(game, tdmap, player, tile);
}

void	draw_background(t_img background, int floor, int sky)
{
	int	i;
	int	j;
	int	color;

	j = 0;
	color = sky;
	while (j < WIN_HEIGHT)
	{
		if (j == WIN_HEIGHT / 2)
			color = floor;
		i = 0;
		while (i < WIN_WIDTH)
		{
			pixel_put(&background, i, j, color);
			i++;
		}
		j++;
	}
}
