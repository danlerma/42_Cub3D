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

t_player	init_player(t_map *map)
{
	int			i;
	int			j;
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
				player.x = (float)j;
				player.y = (float)i;
			}
		}
	}
	player.dir = (float)0;
	if (map->map[(int)player.y][(int)player.x] == 'N')
		player.dir += (M_PI_2);
	else if (map->map[(int)player.y][(int)player.x] == 'S')
		player.dir += (3 * M_PI_2);
	else if (map->map[(int)player.y][(int)player.x] == 'W')
		player.dir += M_PI;
	player.keys = init_keys();
	return (player);
}

void	get_sprites(t_play *game, t_map *map)
{
	game->sprites.north.img = mlx_xpm_file_to_image(game->mlx, map->nsew[0],
			&game->sprites.north.width, &game->sprites.north.height);
	game->sprites.south.img = mlx_xpm_file_to_image(game->mlx, map->nsew[1],
			&game->sprites.south.width, &game->sprites.south.height);
	game->sprites.east.img = mlx_xpm_file_to_image(game->mlx, map->nsew[2],
			&game->sprites.east.width, &game->sprites.east.height);
	game->sprites.west.img = mlx_xpm_file_to_image(game->mlx, map->nsew[3],
			&game->sprites.west.width, &game->sprites.west.height);
	game->sprites.north.data_addr = mlx_get_data_addr(game->sprites.north.img, &game->sprites.north.bpp,
			&game->sprites.north.size_line, &game->sprites.north.endian);
	game->sprites.south.data_addr = mlx_get_data_addr(game->sprites.south.img, &game->sprites.south.bpp,
			&game->sprites.south.size_line, &game->sprites.south.endian);
	game->sprites.east.data_addr = mlx_get_data_addr(game->sprites.east.img, &game->sprites.east.bpp,
			&game->sprites.east.size_line, &game->sprites.east.endian);
	game->sprites.west.data_addr = mlx_get_data_addr(game->sprites.west.img, &game->sprites.west.bpp,
			&game->sprites.west.size_line, &game->sprites.west.endian);
	game->sprites.floor = map->floor; // sprites->floor = get_color(map->floor);
	game->sprites.sky = map->sky; // sprites->sky = get_color(map->sky);
}

void	init_game(t_play *game, t_map *map)
{
	int	size;

	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	game->map = map;
	game->player = init_player(map);
	get_sprites(game, map);
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
