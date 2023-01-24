#include <cub3d.h>

// void	move_player(int key, t_play *game, float angle)
// {
// 	int		dir;
// 	float	new_x;
// 	float	new_y;
// 	float	check_x;
// 	float	check_y;

// 	dir = 1;
// 	if (key == KEY_A || key == KEY_S)
// 		dir = -1;
// 	new_x = game->player.x + (dir * cos(angle));
// 	new_y = game->player.y + (dir * sin(angle));
// 	check_x = game->player.x + MARGIN + new_x;
// 	check_y = game->player.y + MARGIN + new_y;
// 	if (game->map->map[(int)check_y][(int)check_x + MARGIN] != '1')
// 		game->player.y = new_y;
// 	if (game->map->map[(int)check_y + MARGIN][(int)check_x] != '1')
// 		game->player.x = new_x;
// }

void	check_view(t_play *game)
{
	// if(game->player.keys->up)
	// 	move_view();
	// if(game->player.keys->down)
	// 	move_view();
	// if (game->player.keys.left)
	// 	move_view(KEY_LEFT, game);
	// if (game->player.keys.right)
	// 	move_view(KEY_RIGHT, game);
	// printf("-------------> %d\n", game->player.keys.a);
	if (game->player.keys.w)
		printf("move up\n");
		// move_player(KEY_W, game, game->player.dir);
	if (game->player.keys.a)
		printf("move letf\n");
		// move_player(KEY_A, game, game->player.dir + M_PI/2);
	if (game->player.keys.s)
		printf("move down\n");
		// move_player(KEY_S, game, game->player.dir);
	if (game->player.keys.d)
		printf("move right\n");
		// move_player(KEY_D, game, game->player.dir + M_PI/2);
}

static int play_game(t_play *game)
{
	mlx_clear_window(game->mlx, game->win);
	draw_background(game->background, game->map->floor, game->map->sky);
	draw_tdmap(game->tdmap, game->map, game->player);
	// check_view(game);
	// draw_walls(game);
	// draw_minimap();				//pinta minimapa
	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);	// proyectar dibujo en ventana
	mlx_put_image_to_window(game->mlx, game->win, game->tdmap.img, WIN_WIDTH - 10 - game->tdmap.width, 10);	//proyectar mapa 2d en ventana
	return (0);
}

void	do_game(t_map *map, t_play *game)
{
	init_game(game, map);			//variables mlx + datos estructura general
	mlx_loop_hook(game->mlx, play_game, game);	//función juego + struct juego
	// play_game(game);
	mlx_hook(game->win, 2, 1L << 0, k_pressed, game);	//función gestión apretar teclas + struct juego
	mlx_hook(game->win, 3, 1L << 1, k_released, game);	//función gestión soltar teclas + struct juego
	mlx_hook(game->win, 17, 0, close_window, game);		//función cierre redcross + struct juego
	mlx_loop(game->mlx);				//comprobar si hace falta
}
