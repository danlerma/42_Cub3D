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

void draw_player(t_img tdmap, t_player player, t_coord tile, t_coord origin)
{
	t_coord iter;
	int size;

	iter.y = -1;
	size = 5;
	player.x = player.x * tile.x + origin.x - size/2;
	player.y = player.y * tile.y + origin.y - size/2;
	while (++iter.y < size)
	{
		iter.x = -1;
		while (++iter.x < size)
			pixel_put(&tdmap, iter.x + player.x, iter.y + player.y, TDMAP_PLAYER);
	}
}

void draw_tdmap(t_img tdmap, t_map *map, t_player player)
{
	t_coord center;
	t_coord size;
	t_coord	origin;
	t_coord end;
	t_coord iter;
	t_coord tile;
	// float tile_size;

	tile.x = WIN_WIDTH/SCALE /ft_strlen(map->map[0]);
	tile.y = WIN_HEIGHT/SCALE / ft_double_len(map->map);
	// tile_size = (fmax(WIN_HEIGHT, WIN_WIDTH)/SCALE) / fmax(ft_strlen(map->map[0]), ft_double_len(map->map));
	size.x = ft_strlen(map->map[0]) * tile.x;
	size.y = ft_double_len(map->map) * tile.y;
	center.x = WIN_WIDTH/SCALE/2;
	center.y = WIN_HEIGHT/SCALE/2;
	origin.y = center.y - (size.y/2);
	origin.x = center.x - (size.x/2);
	end.x = origin.x + size.x;
	end.y = origin.y + size.y;
	iter.y = 0;
	while (iter.y < end.y)
	{
		origin.x = center.x - (size.x/2);
		iter.x = 0;
		while (iter.x < end.x)
		{
			if (map->map[(int)(iter.y/tile.y)][(int)(iter.x/tile.x)] == '0')
				pixel_put(&tdmap, iter.x + origin.x, iter.y + origin.y, TDMAP_FLOOR);
			else if (map->map[(int)(iter.y/tile.y)][(int)(iter.x/tile.x)] == '1'
				|| map->map[(int)(iter.y/tile.y)][(int)(iter.x/tile.x)] == 32)
				pixel_put(&tdmap, iter.x + origin.x, iter.y + origin.y, TDMAP_WALL);
			else
				pixel_put(&tdmap, iter.x + origin.x, iter.y + origin.y, TDMAP_FLOOR);
			iter.x++;
		}
		iter.y++;
	}
	draw_player(tdmap, player, tile, origin);
}

void draw_background(t_img background, int floor, int sky)
{
	int i;
	int j;
	int color;

	j = 0;
	color = sky;
	while(j < WIN_HEIGHT)
	{
		if(j == WIN_HEIGHT / 2)
			color = floor;
		i = 0;
		while(i < WIN_WIDTH)
		{
			pixel_put(&background, i, j, color);
			i++;
		}
		j++;
	}
}
