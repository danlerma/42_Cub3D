#include <cub3d.h>

void	pixel_put(t_img *background, int i, int j, int color)
{
	char	*dst;

	// if(i == 0 && j == 0)
	// 	printf("direccion pixel -> %p\t%p\t%p\n", &background, background->img, background->data_addr);
	if (i >= 0 && i < WIN_WIDTH && j >= 0 && j < WIN_HEIGHT)
	{
		// printf("ENTRO AQUI\n");
		// pixel = (x * 4) + (y * game->minimap.size_line);
		printf(YELLOW"color %d   i %d    j %d    addr/size/bpp -%s- %d %d\n"RESET, color, i, j, background->data_addr, background->size_line, background->bpp);
		dst = background->data_addr + (j * background->size_line + i * (background->bpp / 8));
		// dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void draw_background(t_img background, int floor, int sky)
{
	int i;
	int j;
	int color;

(void)sky;
// printf("direccion dentr -> %p\t%p\t%p\n", &background, &background.img, &background.data_addr);
	printf("-%s-\n", background.data_addr);
	j = 0;
	color = floor;
	while(j < WIN_HEIGHT)
	{
		// if(j == WIN_HEIGHT / 2)
		// 	color = floor;
		i = 0;
		while(i < WIN_WIDTH)
		{
			// mlx_pixel_put(game->mlx, game->win, i, j, color);
			// (void)background;
			pixel_put(&background, i, j, 0xFF5733);
			i++;
		}
		j++;
	}
	// mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
}


static int play_game(t_play *game)
{
	mlx_clear_window(game->mlx, game->win);
	// printf("direccion fuera -> %p\t%p\t%p\n", &game->background, game->background.img, game->background.data_addr);
	// printf("direccion primer -> %p\t%p\t%p\n", &game->background, &game->background.img, &game->background.data_addr);
	draw_background(game->background, 0xFF5733, 0xFFFFFF);
	// handle_keys(game);
	// draw_walls();				//pinta paredes
	// draw_minimap();				//pinta minimapa
	
	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);	//pproyectar dibujo en ventana
	return (0);
}

// void move_player(int key, t_play *game)
// {
// 	float	new_x;
// 	float	new_y;

// 	if(key == KEY_A)
// 	{
// 		new_x = game->player->x + cos(game->player->dir) * SPEED;
// 		new_y = game->player->y + sin(game->player->dir) * SPEED;
// 		if (game->map->map[(int)game->player->y][(int)game->player->x + ])
// 	}



// }

// void move_view(int key, t_play *game)
// {
// 	if(key == KEY_LEFT)
// 		game->player->dir -= ROTATION;
// 	if(key == KEY_RIGHT)
// 		game->player->dir += ROTATION;
// }

// void handle_keys(t_play *game)
// {
// 	// if(game->player->keys->up)
// 	// 	move_view();
// 	// if(game->player->keys->down)
// 	// 	move_view();
// 	if(game->player->keys->left)
// 		move_view(KEY_LEFT, game);
// 	if(game->player->keys->right)
// 		move_view(KEY_RIGHT, game);
// 	if(game->player->keys->w)
// 		move_player(KEY_W, game);
// 	if(game->player->keys->a)
// 		move_player(KEY_A, game);
// 	if(game->player->keys->s)
// 		move_player(KEY_S, game);
// 	if(game->player->keys->d)
// 		move_player(KEY_D, game);
// }

t_keys	*init_keys(void)
{
	t_keys	*keys;

	keys = malloc(sizeof(t_keys) * 1);
	if (keys == NULL)
		return (keys);
	keys->up = 0;
	keys->down = 0;
	keys->left = 0;
	keys->right = 0;
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	return (keys);
}

t_player	*init_player(t_map *map)
{
	int			i;
	int			j;
	t_player	*player;

	player = malloc(sizeof(t_player) * 1);
	if (player == NULL)
		return (player);
	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
			|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				player->x = (float)j;
				player->y = (float)i;
			}
		}
	}
	player->dir = (float)0;
	if (map->map[(int)player->y][(int)player->x] == 'E')
		player->dir += (M_PI_2);
	else if (map->map[(int)player->y][(int)player->x] == 'S')
		player->dir += M_PI;
	else if (map->map[(int)player->y][(int)player->x] == 'W')
		player->dir += (3 * M_PI_2);
	player->keys = init_keys();
	return (player);
}

void	get_sprites(t_play *game, t_map *map)
{
	// game->sprites = ft_calloc(sizeof(t_sprites), 1);
	// if(game->sprites == NULL)
	// 	error_exit("Calloc failure");	// (void)map;
	game->sprites.north.img = mlx_xpm_file_to_image(game->mlx, map->nsew[0],
			&game->sprites.north.width, &game->sprites.north.height);
	game->sprites.south.img = mlx_xpm_file_to_image(game->mlx, map->nsew[1],
			&game->sprites.south.width, &game->sprites.south.height);
	game->sprites.east.img = mlx_xpm_file_to_image(game->mlx, map->nsew[2],
			&game->sprites.east.width, &game->sprites.east.height);
	game->sprites.west.img = mlx_xpm_file_to_image(game->mlx, map->nsew[3],
			&game->sprites.west.width, &game->sprites.west.height); 		// gestionar tamaños cuando sepa que cojones

	game->sprites.north.data_addr = mlx_get_data_addr(game->sprites.north.img, &game->sprites.north.bpp,
			&game->sprites.north.size_line, &game->sprites.north.endian);
	game->sprites.south.data_addr = mlx_get_data_addr(game->sprites.south.img, &game->sprites.south.bpp,
			&game->sprites.south.size_line, &game->sprites.south.endian);
	game->sprites.east.data_addr = mlx_get_data_addr(game->sprites.east.img, &game->sprites.east.bpp,
			&game->sprites.east.size_line, &game->sprites.east.endian);
	game->sprites.west.data_addr = mlx_get_data_addr(game->sprites.west.img, &game->sprites.west.bpp,
			&game->sprites.west.size_line, &game->sprites.west.endian);
	game->sprites.floor = COLOR_MIENTRAS_SUELO; // sprites->floor = get_color(map->floor);
	game->sprites.sky = COLOR_MIENTRAS_CIELO; // sprites->sky = get_color(map->sky);
}

void	init_game(t_play *game, t_map *map)
{
	// ft_bzero(game, sizeof(t_play));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	game->map = map;
	game->player = init_player(map);
	get_sprites(game, map);
	game->background.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->background.bpp = 32;
	game->background.endian = 1;
	game->background.size_line = game->background.width * (game->background.bpp / 8);
	game->background.data_addr = mlx_get_data_addr(game->background.img,
			&game->background.bpp, &game->background.size_line, &game->background.endian);
	// game->minimap.width = MINIMAP_WIDTH;
	// game->minimap.height = MINIMAP_HEIGHT;
	// game->minimap.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	// game->minimap.data_addr = mlx_get_data_addr(game->minimap.img,
	// 		game->minimap.bpp, game->minimap.size_line, game->minimap.endian);
}

void	do_game(t_map *map, t_play *game)
{
	init_game(game, map);			//variables mlx + datos estructura general
	mlx_loop_hook(game->mlx, play_game, game);	//función juego + struct juego
	mlx_hook(game->win, 2, 1L << 0, k_pressed, game);	//función gestión apretar teclas + struct juego
	mlx_hook(game->win, 2, 1L << 0, k_released, game);	//función gestión soltar teclas + struct juego
	mlx_hook(game->win, 17, 0, close_window, game);		//función cierre redcross + struct juego
	mlx_loop(game->mlx);				//comprobar si hace falta
}
