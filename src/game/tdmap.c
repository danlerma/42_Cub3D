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

void draw_line_ray(t_img tdmap, t_coord pos, t_coord coll, int color) // cambiar por bresenham real
{
	int		i;
	float	dist;
	t_coord	new;

	dist = sqrt(pow(pos.x - coll.x, 2) + pow(pos.y - coll.y, 2));
	new.x = (coll.x - pos.x) / dist;
	new.y = (coll.y - pos.y) / dist;
	i = 0;
	while (i < dist)
	{
		pixel_put(&tdmap, (pos.x + new.x * i), (pos.y + new.y * i),color);
		i++;
	}
}

// void draw_line_ray(t_img tdmap, t_coord pos, t_coord coll, int color)
// {
// 	t_coord	slope;
// 	t_coord	dir;
// 	t_coord	point;
// 	float	diff;
// 	float	aux;

// 	slope.x = coll.x - pos.x;
// 	slope.y = coll.y - pos.y;
// 	if (slope.x < 0)
// 		slope.x *= -1;
// 	if (slope.y < 0)
// 		slope.y *= -1;
// 	dir.x = 1;


	// if (pos.x > coll.x)
	// 	dir.x = -1;
	// dir.y = 1;
	// if (pos.y > coll.y)
	// 	dir.y = -1;
	// diff = slope.x - slope.y;
	// while (point.x != coll.x || point.y != coll.y)
	// {
	// 	pixel_put(&tdmap, point.y, point.y, color);
	// 	aux = diff * 2;
	// 	if (aux > -slope.y)
	// 	{
	// 		diff -= slope.y;
	// 		point.x += dir.x;
	// 	}
	// 	if (aux < slope.x)
	// 	{
	// 		diff += slope.y;
	// 		point.x += dir.x;
	// 	}
	// }
}

void draw_rays(t_play *game, t_img tdmap, float tile)
{
	t_coord	coll;
	t_coord	pos;
	float	ang;
	float	point;

	pos.x = tile * game->player.x;
	pos.y = tile * game->player.y;
	point = 1;
	ang = -M_PI/6;
	while (ang < M_PI/6)
	{
		point = 0;
		coll.x = pos.x + point * cos(game->player.dir + ang);
		coll.y = pos.y + point * sin(game->player.dir + ang);
		while (game->map->map[(int)((pos.y + (int)coll.y - (int)pos.y) / tile)]
				[(int)((pos.x + (int)coll.x - (int)pos.x) / tile)] != '1')
		{
			coll.x = pos.x + point * cos(game->player.dir + ang);
			coll.y = pos.y + point * sin(game->player.dir + ang);
			point += 0.1;
		}
		coll.x = round(coll.x);
		coll.y = round(coll.y);
		draw_line_ray(tdmap, pos, coll, TDMAP_RAYS);
		pixel_put(&tdmap, coll.x, coll.y, 0);
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
	draw_rays(game, tdmap, tile);
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
				// pixel_put(&tdmap, iter.x, iter.y, 16381677);
			else if (map->map[(int)(iter.y / tile)][(int)(iter.x / tile)] == '1'
				|| map->map[(int)(iter.y / tile)][(int)(iter.x / tile)] == 32)
				pixel_put(&tdmap, iter.x, iter.y, TDMAP_WALL);
				// pixel_put(&tdmap, iter.x, iter.y, 15395562);
			else
				pixel_put(&tdmap, iter.x, iter.y, TDMAP_FLOOR);
				// pixel_put(&tdmap, iter.x, iter.y, 16381677);
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
