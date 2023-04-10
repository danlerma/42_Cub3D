#include <cub3d.h>

int	check_movement(t_play *game)
{
	double	i;
	double	j;

	modf((double)game->player.next.x, &i);
	modf((double)game->player.next.y, &j);
	if (game->map->map[(int)j][(int)i] != '1')
	{
		game->player.x = game->player.next.x;
		game->player.y = game->player.next.y;
		return (1);
	}
	return (0);
}

void	move_player(int key, t_play *game)
{
	if (key == KEY_W)
	{
		game->player.next.x += game->player.dir.x * SPEED;
		game->player.next.y += game->player.dir.y * SPEED;
	}
	if (key == KEY_A)
	{
		game->player.next.x += game->player.dir.y * SPEED;
		game->player.next.y -= game->player.dir.x * SPEED;
	}
	if (key == KEY_S)
	{
		game->player.next.x -= game->player.dir.x * SPEED;
		game->player.next.y -= game->player.dir.y * SPEED;
	}
	if (key == KEY_D)
	{
		game->player.next.x -= game->player.dir.y * SPEED;
		game->player.next.y += game->player.dir.x * SPEED;
	}
}

void	move_view(int key, t_play *game)
{
	double	start_dir;
	double	start_plane;
	int		dir;

	dir = 1;
	if (key == KEY_RIGHT)
		dir = -1;
	start_dir = game->player.dir.x;
	start_plane = game->player.plane.x;
	game->player.dir.x = game->player.dir.x * cos(ROT_ANGLE * dir) - game->player.dir.y * sin(ROT_ANGLE * dir);
	game->player.dir.y = start_dir * sin(ROT_ANGLE * dir) + game->player.dir.y * cos(ROT_ANGLE * dir);
	game->player.plane.x = game->player.plane.x * cos(ROT_ANGLE * dir) - game->player.plane.y * sin(ROT_ANGLE * dir);
	game->player.plane.y = start_plane * sin(ROT_ANGLE * dir) + game->player.plane.y * cos(ROT_ANGLE * dir);
	game->player.ang += (ROT_ANGLE * dir);
}

void	check_view(t_play *game)
{
	game->player.next.x = game->player.x;
	game->player.next.y = game->player.y;
	if (game->player.keys.left)
		move_view(KEY_LEFT, game);
	if (game->player.keys.right)
		move_view(KEY_RIGHT, game);
	if (game->player.keys.w)
		move_player(KEY_W, game);
	if (game->player.keys.a)
		move_player(KEY_A, game);
	if (game->player.keys.s)
		move_player(KEY_S, game);
	if (game->player.keys.d)
		move_player(KEY_D, game);
	if (check_movement(game))
	{
		game->player.x = game->player.next.x;
		game->player.y = game->player.next.y;
	}
}

static int	play_game(t_play *game)
{
	draw_background(game->background, game->map->floor, game->map->sky);
	check_view(game);
	do_walls(game);
	draw_tdmap(game, game->tdmap, game->map, game->player);
	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->raycast.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->tdmap.img, WIN_WIDTH - 10 - game->tdmap.width, 10);
	return (0);
}

void	do_game(t_map *map, t_play *game)
{
	init_game(game, map);			//variables mlx + datos estructura general
	mlx_loop_hook(game->mlx, play_game, game);	//función juego + struct juego
	mlx_hook(game->win, 2, 1L << 0, k_pressed, game);	//función gestión apretar teclas + struct juego
	mlx_hook(game->win, 3, 1L << 1, k_released, game);	//función gestión soltar teclas + struct juego
	mlx_hook(game->win, 17, 0, close_window, game);		//función cierre redcross + struct juego
	mlx_loop(game->mlx);				//comprobar si hace falta
}
