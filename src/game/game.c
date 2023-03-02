#include <cub3d.h>

void	move_player(int key, t_play *game, float angle)
{
	int		dir;
	t_coord	new;

	dir = 1;
	if (key == KEY_W || key == KEY_A)
		dir = -1;
	new.x = game->player.x + (cos(angle) * dir * SPEED);
	new.y = game->player.y + (sin(angle) * dir * SPEED);
	if (game->map->map[(int)new.y][(int)(game->player.x)] != '1')
		game->player.y = new.y;
	if (game->map->map[(int)(game->player.y)][(int)new.x] != '1')
		game->player.x = new.x;
}

void move_view(int key, t_play *game)
{
	int dir;

	dir = 1;
	if (key == KEY_RIGHT)
		dir = -1;
	game->player.dir += (dir * SPEED);
}

void	check_view(t_play *game)
{
	// if(game->player.keys->up)
	// 	move_view();
	// if(game->player.keys->down)
	// 	move_view();
	if (game->player.keys.left)
		move_view(KEY_LEFT, game);
	if (game->player.keys.right)
		move_view(KEY_RIGHT, game);
	if (game->player.keys.w)
		move_player(KEY_W, game, game->player.dir + M_PI_2);
	if (game->player.keys.a)
		move_player(KEY_A, game, game->player.dir);
	if (game->player.keys.s)
		move_player(KEY_S, game, game->player.dir + M_PI_2);
	if (game->player.keys.d)
		move_player(KEY_D, game, game->player.dir);
}

static int play_game(t_play *game)
{
	mlx_clear_window(game->mlx, game->win);
	draw_background(game->background, game->map->floor, game->map->sky);
	check_view(game);
	// draw_walls(game);
	draw_tdmap(game, game->tdmap, game->map, game->player);
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
