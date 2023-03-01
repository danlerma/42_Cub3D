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

void draw_rays(t_play *game, t_img tdmap, float tile)
{
	t_coord	coll;	// collision point
	// t_coord	coord;
	// float	ray_len;
	// int	i;

	(void)game;
	(void)tile;
	pixel_put(&tdmap, 0, 0, 0);
	coll.x = 0;
	coll.y = 0;
	printf("p -> %f - %f\n", game->player.x, game->player.y);
	while(1)
	{
		if(game->map->map[(int)game->player.y][(int)game->player.x + (int)coll.x] != '1')
			coll.x += 0.01;
		if(game->map->map[(int)game->player.y + (int)coll.y][(int)game->player.x] != '1')
			coll.y += 0.01;
		if (game->map->map[(int)game->player.y + (int)coll.y][(int)game->player.x] == '1'
			&& game->map->map[(int)game->player.y][(int)game->player.x + (int)coll.x] == '1')
			break;
	}
	printf(YELLOW"c -> %f - %f\n"RESET, coll.x, coll.y);
	printf(GREEN"%d - %d\n"RESET, ft_double_len(game->map->map), (int)ft_strlen(game->map->map[0]));
	pixel_put(&tdmap, game->player.x*tile, coll.y*tile, 0);
	pixel_put(&tdmap, coll.x*tile, game->player.y*tile, 0);
	// pixel_put(&tdmap, ft_double_len(game->map->map)* tile, (int)ft_strlen(game->map->map[0]) * tile, 16711680);


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
	pixel_put(&tdmap, (tile * ft_strlen(game->map->map[0])), 0, 16711680);
	while (++iter.y < size)
	{
		iter.x = -1;
		while (++iter.x < size)
			pixel_put(&tdmap, iter.x + pos.x, iter.y + pos.y, TDMAP_PLAYER);
	}
	draw_rays(game, tdmap, tile);
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
