#include <cub3d.h>

// void draw_walls()
// {
// 	movement();
// 	raycasting();
// 	bresenham();
	
// }



void	pixel_put(t_img *background, int i, int j, int color)
{
	char	*dst;

	if (i >= 0 && i < background->width && j >= 0 && j < background->height)
	{
		dst = background->data_addr + (j * background->size_line
				+ i * (background->bbp / 8));
		*(unsigned int *)dst = color;
	}
}

void draw_background(t_img *background, int floor, int sky)
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
			pixel_put(background, i, j, color);
			i++;
		}
		j++;
	}
}

int play_game(void *g)
{
	t_play *game = g;
	mlx_clear_window(game->mlx, game->win);
	draw_background(&game->background, COLOR_MIENTRAS_SUELO, COLOR_MIENTRAS_CIELO);
	// draw_walls();				//pinta paredes
	// draw_minimap();				//pinta minimapa
	// mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
	// mlx_put_image_to_window();	//pproyectar dibujo en ventana
	return (0);
}

t_keys *init_keys(void)
{
	t_keys *keys;

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
	return(keys);
}


t_player *init_player(t_map *map)
{
	int i;
	int j;
	t_player *player;

	player = malloc(sizeof(t_player) * 1);
	if (player == NULL)
		return (player);
	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while(map->map[i][++j])
		{
			if(map->map[i][j] == 'N' || map->map[i][j] == 'S'
			|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				player->x = (float)j;
				player->y = (float)i;
			}
		}
	}
	player->dir = (float)0;
	if(map->map[(int)player->y][(int)player->x] == 'E')
		player->dir += (M_PI_2);
	else if(map->map[(int)player->y][(int)player->x] == 'S')
		player->dir += M_PI;
	else if(map->map[(int)player->y][(int)player->x] == 'W')
		player->dir += (3 * M_PI_2);
	player->keys = init_keys();
	return(player);
}


// // comprobar que formato de comas sea valido
// // hacer splt
// // comprobar que haya 3 valores
// // comprobar quue son todo dígitos
// // comprobar que están entre 0 y 255


t_sprites *get_sprites(t_play *game, t_map *map)
{
	t_sprites *sprites;

	sprites = malloc(sizeof(t_sprites) * 1);
	if(sprites == NULL)
		return(sprites);
	// (void)map;
	// (void)game;

	game->sprites->north.width = 0;
	game->sprites->north.height = 0;
	printf("------> %s %d\n",map->nsew[0], game->sprites->north.width);
	sprites->north.img = mlx_xpm_file_to_image(game->mlx, map->nsew[0],
			0,0);
	// sprites->south.img = mlx_xpm_file_to_image(game->mlx, map->nsew[1],
	// 		&game->sprites->south.width, &game->sprites->south.height);
	// sprites->east.img = mlx_xpm_file_to_image(game->mlx, map->nsew[2],
	// 		&game->sprites->east.width, &game->sprites->east.height);
	// sprites->west.img = mlx_xpm_file_to_image(game->mlx, map->nsew[3],
	// 		&game->sprites->west.width, &game->sprites->west.height); 		// gestionar tamaños cuando sepa que cojones

	// sprites->north.data_addr = mlx_get_data_addr(game->sprites->north.img, &game->sprites->north.bbp,
	// 		&game->sprites->north.size_line, &game->sprites->north.endian);
	// sprites->south.data_addr = mlx_get_data_addr(game->sprites->south.img, &game->sprites->south.bbp,
	// 		&game->sprites->south.size_line, &game->sprites->south.endian);
	// sprites->east.data_addr = mlx_get_data_addr(game->sprites->east.img, &game->sprites->east.bbp,
	// 		&game->sprites->east.size_line, &game->sprites->east.endian);
	// sprites->west.data_addr = mlx_get_data_addr(game->sprites->west.img, &game->sprites->west.bbp,
	// 		&game->sprites->west.size_line, &game->sprites->west.endian);
	sprites->floor = COLOR_MIENTRAS_SUELO; // sprites->floor = get_color(map->floor);
	sprites->sky = COLOR_MIENTRAS_CIELO; // sprites->sky = get_color(map->sky);
	return (sprites);
}

void init_game(t_play *game, t_map *map)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	game->map = map;
	game->player = init_player(map);
	game->sprites = get_sprites(game, map);
	game->background.width = WIN_WIDTH;
	game->background.height = WIN_HEIGHT;
	game->background.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->background.data_addr = mlx_get_data_addr(game->background.img,
			&game->background.bbp, &game->background.size_line, &game->background.endian);
	// game->minimap.width = MINIMAP_WIDTH;
	// game->minimap.height = MINIMAP_HEIGHT;
	// game->minimap.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	// game->minimap.data_addr = mlx_get_data_addr(game->minimap.img,
	// 		game->minimap.bbp, game->minimap.size_line, game->minimap.endian);
	
}

void game(t_map *map)
{
	t_play game;

	ft_bzero(&game, sizeof(t_play));
	init_game(&game, map);			//variables mlx + datos estructura general
	// mlx_loop_hook(game.mlx, play_game, &game);	//función juego + struct juego
	// mlx_hook(mlx->win, 2, 1L << 0, k_pressed, game);	//función gestión apretar teclas + struct juego
	// mlx_hook(mlx->win, 2, 1L << 0, k_released, game);	//función gestión soltar teclas + struct juego
	printf("\n\n PROBANDO\n");
	// check_movement();
	// mlx_hook(mlx->win, 17, 0, close_window, game);		//función cierre redcross + struct juego
	// mlx_loop(mlx->mlx);				//comprobar si hace falta

}




/*

void	so_long(t_mlx *mlx, t_map *map)
{
	t_sprites	sprites;
	t_all		game;

	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
		print_error();
	mlx->win = mlx_new_window(mlx->mlx,
			(map->size_x - 1) * 32, map->size_y * 32, "so_long");
	if (mlx->win == NULL)
	{
		mlx_destroy_image(mlx->mlx, mlx->image);
		ft_free_double(map->coords);
		print_error();
	}
	sprites = get_sprites(mlx);
	draw_map(mlx, map, &sprites);
	game = join_all(mlx, map, &sprites);
	mlx_key_hook(game.mlx.win, handle_keypress, &game);
	mlx_hook(game.mlx.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx.mlx);
}




int	initialise_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->img.img = mlx_new_image(vars->mlx, WIN_W, WIN_H);
	vars->img.addr = mlx_get_data_addr(vars->img.img,
			&vars->img.bpp, &vars->img.line_len, &vars->img.endian);
	vars->win = mlx_new_window(vars->mlx, WIN_W, WIN_H, "cub3D");
	initialise_minimap(vars);
	if (init_textures(vars) != 0)
		return (1);
	return (0);
}


// void	so_long(t_mlx *mlx, t_map *map)
// {
// 	t_sprites	sprites;
// 	t_all		game;

// 	mlx->mlx = mlx_init();
// 	if (mlx->mlx == NULL)
// 		print_error();
// 	mlx->win = mlx_new_window(mlx->mlx,
// 			(map->size_x - 1) * 32, map->size_y * 32, "so_long");
// 	if (mlx->win == NULL)
// 	{
// 		mlx_destroy_image(mlx->mlx, mlx->image);
// 		ft_free_double(map->coords);
// 		print_error();
// 	}
// 	sprites = get_sprites(mlx);
// 	draw_view(mlx, map, &sprites);
// 	draw_minimap(mlx, map, &sprites);
// 	mlx_loop_hook(game.mlx.mlx, do_game(), &game);
// 	// mlx_key_hook(game.mlx.win, handle_keypress, &game);
// 	mlx_hook(game.mlx.win, 17, 0, close_window, &game);
// 	mlx_loop(game.mlx.mlx);
// }

*/








// static void	move_player(t_game *g, int dir, float angle)
// {
// 	float	new_pos_x;
// 	float	new_pos_y;
// 	float	check_pos_x;
// 	float	check_pos_y;

// 	g->player.step_x = dir * (cos(angle) * PLAYER_SPEED);
// 	g->player.step_y = dir * (sin(angle) * PLAYER_SPEED);
// 	new_pos_x = g->player.x + g->player.step_x;
// 	new_pos_y = g->player.y + g->player.step_y;
// 	check_pos_x = g->player.x + 0.5 + (5 * g->player.step_x);
// 	check_pos_y = g->player.y + 0.5 + (5 * g->player.step_y);
// 	if (g->map[(int)check_pos_y][(int)(g->player.x + 0.5)] != '1')
// 		g->player.y = new_pos_y;
// 	if (g->map[(int)(g->player.y + 0.5)][(int)check_pos_x] != '1')
// 		g->player.x = new_pos_x;
// }

// void	check_movement(t_game *g)
// {
// 	if (g->player.key.w)
// 		move_player(g, 1, g->player.angle);
// 	if (g->player.key.s)
// 		move_player(g, -1, g->player.angle);
// 	if (g->player.key.a)
// 		move_player(g, -1, g->player.angle + DEGREES_90);
// 	if (g->player.key.d)
// 		move_player(g, 1, g->player.angle + DEGREES_90);
// 	if (g->player.key.left)
// 		g->player.angle -= PLAYER_ROTATE;
// 	if (g->player.key.right)
// 		g->player.angle += PLAYER_ROTATE;
// }
