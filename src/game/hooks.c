#include <cub3d.h>

int	close_window(t_play *game)
{
	mlx_destroy_image(game->mlx, game->background.img);
	// mlx_destroy_image(game->mlx, game->minimap.img);
	// mlx_destroy_image(game->mlx, &game->sprites.north);
	// mlx_destroy_image(game->mlx, &game->sprites.south);
	// mlx_destroy_image(game->mlx, &game->sprites.east);
	// mlx_destroy_image(game->mlx, &game->sprites.west);
	mlx_destroy_window(game->mlx, game->win);
	// ft_free_malloc(game->map);
	exit(0);
	return (0);
}

int	k_pressed(int key, t_play *game)
{
	if (key == KEY_ESC)
		close_window(game);
	else if (key == KEY_W)
		game->player.keys.w = 1;
	else if (key == KEY_A)
		game->player.keys.a = 1;
	else if (key == KEY_S)
		game->player.keys.s = 1;
	else if (key == KEY_D)
		game->player.keys.d = 1;
	else if (key == KEY_LEFT)
		game->player.keys.left = 1;
	else if (key == KEY_RIGHT)
		game->player.keys.right = 1;
	return (0);
}

int	k_released(int key, t_play *game)
{
	if (key == KEY_W)
		game->player.keys.w = 0;
	else if (key == KEY_A)
		game->player.keys.a = 0;
	else if (key == KEY_S)
		game->player.keys.s = 0;
	else if (key == KEY_D)
		game->player.keys.d = 0;
	else if (key == KEY_LEFT)
		game->player.keys.left = 0;
	else if (key == KEY_RIGHT)
		game->player.keys.right = 0;
	return (0);
}
