#include <cub3d.h>







int get_sprite_pixel(t_play *game, t_img *sprite, t_coord ray, int j)
{
	int color;
	int i;
	// char *pixel;

	color = 0;
	i =  (int)(sprite->width * (ray.y + ray.y)) % sprite->width;
	if (game->map->map[(int)ray.y][(int)ray.x] == '1')
	{
		color = *(unsigned int *)(sprite->data_addr + (i * sprite->size_line + j * (sprite->bpp / 8)));
	}
	return (color);
}

t_img get_sprite(t_play *game, t_coord ray, float ang)
{
	t_img	sprite;
	t_coord	next;

	next.x = cos(ang) / 90;
	next.y = sin(ang) / 90;
	ft_bzero(&sprite, sizeof(t_img));
	if (next.x < 0)
		next.x *= -1;
	if (next.y < 0)
		next.y *= -1;
	if (game->map->map[(int)(ray.y - next.y)][(int)ray.x] != '1')
		sprite = game->sprites.north;
	else if (game->map->map[(int)(ray.y + next.y)][(int)ray.x] != '1')
		sprite = game->sprites.south;
	else if(game->map->map[(int)(ray.y)][(int)(ray.x - next.x)] != '1')
		sprite = game->sprites.west;
	else if (game->map->map[(int)(ray.y)][(int)(ray.x + next.x)] != '1')
		sprite = game->sprites.east;
	return(sprite);
}

float get_dist(t_play *game, t_coord ray, float ang)
{
	float	dist;
	float	wall_height;

	dist = sqrt(pow(ray.x - game->player.x, 2) + pow(ray.y - game->player.y, 2));
	dist = dist * cos(ang - game->player.dir);
	wall_height = WIN_HEIGHT/2/dist;
	return (wall_height);
}

void define_pos(t_play *game, t_coord *ray, t_coord *arit, float ang)
{
	ray->x = game->player.x;
	ray->y = game->player.y;
	arit->x = cos(ang) / 90;
	arit->y = sin(ang) / 90;
	while (game->map->map[(int)ray->y][(int)ray->x] != '1')
	{
		ray->x += arit->x;
		ray->y += arit->y;
	}
}

void draw_walls(t_play *game, t_img sprite, t_coord ray, float frame, float wall_height)
{
	int i;
	int j;
	float next;
	t_coord	start;
	t_coord	end;
	int color;

	next = wall_height * 2 / sprite.height;
	start.x = frame;
	end.x = frame;
	start.y = WIN_HEIGHT/2 - wall_height;
	i = 0;
	while (i < sprite.height)
	{
		color = get_sprite_pixel(game, &sprite, ray, i);
		j = start.y;
		while (j < start.y + next)
			j++;
		end.y = j;
		draw_line_ray(game->background, start, end, color);
		start.y += next;
		i++;
	}
}

void do_walls(t_play *game)
{
	float	ang;
	t_coord	ray;
	t_coord	arit;
	int		frame;
	float	wall_height;
	t_img	sprite;

	ang = game->player.dir - (M_PI / 6);
	frame = 0;
	while (frame < WIN_WIDTH)
	{
		// ray.x = game->player.x;
		// ray.y = game->player.y;
		// arit.x = cos(ang) / 90;
		// arit.y = sin(ang) / 90;
		// while (game->map->map[(int)ray.y][(int)ray.x] != '1')
		// {
		// 	ray.x += arit.x;
		// 	ray.y += arit.y;
		// }
		// ammend_fisheye(game, ray, ang, frame);
		define_pos(game, &ray, &arit, ang);
		wall_height = get_dist(game, ray, ang);
		sprite = get_sprite(game, ray, ang);
		draw_walls(game, sprite, ray, frame, wall_height);
		ang += (M_PI/3)/WIN_WIDTH;
		frame++;	
	}
}
