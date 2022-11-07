#include <cub3d.h>

// void draw_walls()
// {
// 	raycasting();
// 	bresenham();
	
// }


// void play_game(t_play *game)
// {
// 	mlx_clear_window(mlx->mlx, mlx->win);
// 	draw_background();			//pinta fondo cielo y suelo		comprobar si esto hace un segfault en la primera vuelta
// 	draw_walls();				//pinta paredes
// 	draw_minimap();				//pinta minimapa
// 	mlx_put_image_to_window();	//pproyectar dibujo en ventana
// }

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

void init_game(t_play *game, t_map *map)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window();
	game->map = map;
	game->player = init_player(map);
	// game->sprites = get_sprites(game, map);
}

void game(t_map *map)
{
	t_play game;


	init_game(&game, map);			//variables mlx + datos estructura general
	printf("PROBANDO\n");
	// mlx_loop_hook(mlx->mlx, play_game, game);	//función juego + struct juego
	// mlx_hook(mlx->win, 2, 1L << 0, k_pressed, game);	//función gestión apretar teclas + struct juego
	// mlx_hook(mlx->win, 2, 1L << 0, k_released, game);	//función gestión soltar teclas + struct juego
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