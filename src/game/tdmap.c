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

void	draw_player(t_img tdmap, t_player player, float tile, t_coord origin)
{
	t_coord	iter;
	int		size;

	iter.y = -1;
	size = 5;
	player.x = player.x * tile + origin.x - size / 2;
	player.y = player.y * tile + origin.y - size / 2;
	while (++iter.y < size)
	{
		iter.x = -1;
		while (++iter.x < size)
			pixel_put(&tdmap, iter.x + player.x, iter.y + player.y, TDMAP_PLAYER);
	}
}

void	draw_tdmap(t_img tdmap, t_map *map, t_player player)
{
	t_coord	origin;
	t_coord	iter;
	float	tile;

	tile = tdmap.width / ft_strlen(map->map[0]);
	origin.y = tdmap.height / 2 - (tdmap.height / 2);
	origin.x = tdmap.width / 2 - (tdmap.width / 2);
	iter.y = 0;
	while (iter.y < (origin.y + tdmap.height))
	{
		iter.x = 0;
		while (iter.x < (origin.x + tdmap.width))
		{
			if (map->map[(int)(iter.y / tile)][(int)(iter.x / tile)] == '0')
				pixel_put(&tdmap, iter.x + origin.x, iter.y + origin.y, TDMAP_FLOOR);
			else if (map->map[(int)(iter.y / tile)][(int)(iter.x / tile)] == '1'
				|| map->map[(int)(iter.y / tile)][(int)(iter.x / tile)] == 32)
				pixel_put(&tdmap, iter.x + origin.x, iter.y + origin.y, TDMAP_WALL);
			else
				pixel_put(&tdmap, iter.x + origin.x, iter.y + origin.y, TDMAP_FLOOR);
			iter.x++;
		}
		iter.y++;
	}
	draw_player(tdmap, player, tile, origin);
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
