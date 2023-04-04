#include <cub3d.h>

t_keys	init_keys(void)
{
	t_keys	keys;

	keys.up = 0;
	keys.down = 0;
	keys.left = 0;
	keys.right = 0;
	keys.w = 0;
	keys.a = 0;
	keys.s = 0;
	keys.d = 0;
	return (keys);
}

void def_dir(t_player *player, char dir)
{
		if (dir == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
	}
	if (dir == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
	}
	if (dir == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
	}
	if (dir == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
	}
	player->plane.x = player->dir.y * -0.66;
	player->plane.y = player->dir.x * -0.66;
}

t_player	init_player(t_map *map)
{
	int			i;
	int			j;
	char		dir;
	t_player	player;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
			|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				player.x = (float)j + 0.5;
				player.y = (float)i + 0.5;
				dir = map->map[i][j];
			}
		}
	}
	def_dir(&player, dir);
	player.keys = init_keys();
	// ft_bzero(&player.next, sizeof(t_coord));
	return (player);
}

// t_img	init_img(t_play *game, char *dir)
// {
// 	t_img	img;

// 	img.img = mlx_xpm_file_to_image(game->mlx, dir, &img.width, &img.height);
// 	if (!img.img)
// 		return (img);
// 	img.data_addr = mlx_get_data_addr(img.img, &img.bpp, &img.size_line, &img.endian);
// 	return (img);
// }

t_sprites	get_sprites(t_play *game, t_map *map)
{
	t_sprites	sprites;

	sprites.north.img = mlx_xpm_file_to_image(game->mlx, map->nsew[0],
			&sprites.north.width, &sprites.north.height);
	sprites.south.img = mlx_xpm_file_to_image(game->mlx, map->nsew[1],
			&sprites.south.width, &sprites.south.height);
	sprites.east.img = mlx_xpm_file_to_image(game->mlx, map->nsew[2],
			&sprites.east.width, &sprites.east.height);
	sprites.west.img = mlx_xpm_file_to_image(game->mlx, map->nsew[3],
			&sprites.west.width, &sprites.west.height);
	sprites.north.data_addr = mlx_get_data_addr(sprites.north.img, &sprites.north.bpp,
			&sprites.north.size_line, &sprites.north.endian);
	sprites.south.data_addr = mlx_get_data_addr(sprites.south.img, &sprites.south.bpp,
			&sprites.south.size_line, &sprites.south.endian);
	sprites.east.data_addr = mlx_get_data_addr(sprites.east.img, &sprites.east.bpp,
			&sprites.east.size_line, &sprites.east.endian);
	sprites.west.data_addr = mlx_get_data_addr(sprites.west.img, &sprites.west.bpp,
			&sprites.west.size_line, &sprites.west.endian);
	sprites.floor = map->floor; // sprites->floor = get_color(map->floor);
	sprites.sky = map->sky; // sprites->sky = get_color(map->sky);
	return (sprites);
}

void	init_game(t_play *game, t_map *map)
{
	int	size;

	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	game->raycast.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->raycast.data_addr = mlx_get_data_addr(game->raycast.img,
			&game->raycast.bpp, &game->raycast.size_line, &game->raycast.endian);
	game->map = map;
	game->player = init_player(map);
	game->sprites = get_sprites(game, map);
	game->background.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->background.size_line = game->background.width * (game->background.bpp / 8);
	game->background.data_addr = mlx_get_data_addr(game->background.img,
			&game->background.bpp, &game->background.size_line, &game->background.endian);
	size = fmin(WIN_WIDTH / SCALE / ft_strlen(map->map[0]), WIN_HEIGHT / SCALE / ft_double_len(map->map));
	game->tdmap.width = size * ft_strlen(map->map[0]);
	game->tdmap.height = size * ft_double_len(map->map);
	game->tdmap.img = mlx_new_image(game->mlx, game->tdmap.width, game->tdmap.height);
	game->tdmap.size_line = game->tdmap.width * (game->tdmap.bpp / 8);
	game->tdmap.data_addr = mlx_get_data_addr(game->tdmap.img,
			&game->tdmap.bpp, &game->tdmap.size_line, &game->tdmap.endian);
}
