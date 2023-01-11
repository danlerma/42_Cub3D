#include <cub3d.h>

void put_walls(t_play *game, t_img text, t_coord ray, int count)
{
	int i;
	float j;
	float y;
	int color;
	t_coord wall;

	y =

}

t_img get_text(t_play *game, t_coord ray, float ray_angle)
{
	t_img text;
	float x;
	float y;
	x = cos(ray_angle) / 90;
	y = sin(ray_angle) / 90;
	if (x < 0)
		x *= -1;
	if (y < 0)
		y *= -1;
	if (game->map->map[(int)(ray.y - y)][(int)ray.x] != '1')
		text = game->sprites.north;
	else if (game->map->map[(int)(ray.y + y)][(int)ray.x] != '1')
		text = game->sprites.south;
	else if (game->map->map[(int)ray.y][(int)(ray.x - x)] != '1')
		text = game->sprites.west;
	else if (game->map->map[(int)ray.y][(int)(ray.x + x)] != '1')
		text = game->sprites.east;
	return (text);
}

void wall_dist(t_play *game, int count, float ray_angle, t_coord ray)
{
	float dist;
	t_img text;
	float wall;

	dist = sqrt(pow(ray.x - game->player.x - 0.5, 2)
		+ pow(ray.y - game->player.y - 0.5, 2));
	dist = dist * cos(ray_angle - game->player.dir);
	wall = WIN_HEIGHT * 2 / 3 / dist;
	text = get_text(game, ray, ray_angle);
	put_walls(game, text, ray, count);
}

void draw_walls(t_play *game)
{
	int count;
	float ray_angle;
	float ray_cos;
	float ray_sin;
	t_coord ray;

	count = 0;
	ray_angle = game->player.dir - ANGLE_THIRTY;
	while (count < WIN_WIDTH)
	{
		ray.x = game->player.x + 0.5;
		ray.y = game->player.y + 0.5;
		ray_cos = cos(ray_angle) / 90;
		ray_sin = sin(ray_angle) / 90;
		while (game->map->map[(int)floor(ray.y)][(int)floor(ray.x)] != '1')
		{
			ray.x += ray_cos;
			ray.y += ray_sin;
		}
		wall_dist(game, count, ray_angle, ray);
		ray_angle += ANGLE_SIXTY / WIN_WIDTH;
		count++;
	}


}



// static int play_game(t_play *game)
// {
// 	mlx_clear_window(game->mlx, game->win);
// 	draw_background(game->background, game->map->floor, game->map->sky);
// 	draw_tdmap(game->tdmap, game->map, game->player);
// 	// check_view(game);
// 	// draw_walls();				//pinta paredes
// 	// draw_minimap();				//pinta minimapa
// 	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);	//pproyectar dibujo en ventana
// 	mlx_put_image_to_window(game->mlx, game->win, game->tdmap.img, WIN_WIDTH - 10 - fmax(WIN_HEIGHT,WIN_WIDTH)/SCALE, 10);	//proyectar mapa 2d en ventana
// 	return (0);
// }

// void	do_game(t_map *map, t_play *game)
// {
// 	init_game(game, map);			//variables mlx + datos estructura general
// 	mlx_loop_hook(game->mlx, play_game, game);	//función juego + struct juego
// 	// play_game(game);
// 	mlx_hook(game->win, 2, 1L << 0, k_pressed, game);	//función gestión apretar teclas + struct juego
// 	mlx_hook(game->win, 3, 1L << 1, k_released, game);	//función gestión soltar teclas + struct juego
// 	mlx_hook(game->win, 17, 0, close_window, game);		//función cierre redcross + struct juego
// 	mlx_loop(game->mlx);				//comprobar si hace falta
// }

