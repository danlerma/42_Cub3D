#include <cub3d.h>







// int get_sprite_pixel(t_play *game, t_img *sprite, t_coord ray, int j)
// {
// 	int color;
// 	int i;
// 	// char *pixel;

// 	color = 0;
// 	i =  (int)(sprite->width * (ray.y + ray.y)) % sprite->width;
// 	if (game->map->map[(int)ray.y][(int)ray.x] == '1')
// 	{
// 		color = *(unsigned int *)(sprite->data_addr + (i * sprite->size_line + j * (sprite->bpp / 8)));
// 	}
// 	return (color);
// }

// t_img get_sprite(t_play *game, t_coord ray, float ang)
// {
// 	t_img	sprite;
// 	t_coord	next;

// 	next.x = cos(ang) / 90;
// 	next.y = sin(ang) / 90;
// 	ft_bzero(&sprite, sizeof(t_img));
// 	if (next.x < 0)
// 		next.x *= -1;
// 	if (next.y < 0)
// 		next.y *= -1;
// 	if (game->map->map[(int)(ray.y - next.y)][(int)ray.x] != '1')
// 		sprite = game->sprites.north;
// 	else if (game->map->map[(int)(ray.y + next.y)][(int)ray.x] != '1')
// 		sprite = game->sprites.south;
// 	else if(game->map->map[(int)(ray.y)][(int)(ray.x - next.x)] != '1')
// 		sprite = game->sprites.west;
// 	else if (game->map->map[(int)(ray.y)][(int)(ray.x + next.x)] != '1')
// 		sprite = game->sprites.east;
// 	return(sprite);
// }

// float get_dist(t_play *game, t_coord ray, float ang)
// {
// 	float	dist;
// 	float	wall_height;

// 	dist = sqrt(pow(ray.x - game->player.x, 2) + pow(ray.y - game->player.y, 2));
// 	dist = dist * cos(ang - game->player.dir);
// 	wall_height = WIN_HEIGHT/2/dist;
// 	return (wall_height);
// }

// void define_pos(t_play *game, t_coord *ray, t_coord *arit, float ang)
// {
// 	ray->x = game->player.x;
// 	ray->y = game->player.y;
// 	arit->x = cos(ang) / 90;
// 	arit->y = sin(ang) / 90;
// 	while (game->map->map[(int)ray->y][(int)ray->x] != '1')
// 	{
// 		ray->x += arit->x;
// 		ray->y += arit->y;
// 	}
// }

// void draw_walls(t_play *game, t_img sprite, t_coord ray, float frame, float wall_height)
// {
// 	int i;
// 	int j;
// 	float next;
// 	t_coord	start;
// 	t_coord	end;
// 	int color;

// 	next = wall_height * 2 / sprite.height;
// 	start.x = frame;
// 	end.x = frame;
// 	start.y = WIN_HEIGHT/2 - wall_height;
// 	i = 0;
// 	while (i < sprite.height)
// 	{
// 		color = get_sprite_pixel(game, &sprite, ray, i);
// 		j = start.y;
// 		while (j < start.y + next)
// 			j++;
// 		end.y = j;
// 		draw_line_ray(game->background, start, end, color);
// 		start.y += next;
// 		i++;
// 	}
// }

// void do_walls(t_play *game)
// {
// 	float	ang;
// 	t_coord	ray;
// 	t_coord	arit;
// 	int		frame;
// 	float	wall_height;
// 	t_img	sprite;

// 	ang = game->player.dir - (M_PI / 6);
// 	frame = 0;
// 	while (frame < WIN_WIDTH)
// 	{
// 		// ray.x = game->player.x;
// 		// ray.y = game->player.y;
// 		// arit.x = cos(ang) / 90;
// 		// arit.y = sin(ang) / 90;
// 		// while (game->map->map[(int)ray.y][(int)ray.x] != '1')
// 		// {
// 		// 	ray.x += arit.x;
// 		// 	ray.y += arit.y;
// 		// }
// 		// ammend_fisheye(game, ray, ang, frame);
// 		define_pos(game, &ray, &arit, ang);
// 		wall_height = get_dist(game, ray, ang);
// 		sprite = get_sprite(game, ray, ang);
// 		draw_walls(game, sprite, ray, frame, wall_height);
// 		ang += (M_PI/3)/WIN_WIDTH;
// 		frame++;	
// 	}
// }

t_img get_sprite(t_play *game, t_rayc *ray)
{
	if (ray->side == 0 && ray->dir_x < 0)
		return (game->sprites.north);
	else if (ray->side == 0 && ray->dir_x > 0)
		return (game->sprites.south);
	else if (ray->side == 1 && ray->dir_y < 0)
		return (game->sprites.west);
	else
		return (game->sprites.east);
}

unsigned long	rgb_to_hex(int r, int g, int b, int a)
{
	unsigned long	hex;

	hex = ((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8)
		+ (b & 0xff);
	return (hex);
}

uint32_t	pixel_get(t_img *sprite, int x, int y)
{
	unsigned int	dst;
	uint32_t		color;

	dst = *(unsigned int *)(sprite->data_addr
			+ (y * sprite->size_line + x * (sprite->bpp / 8)));
	color = rgb_to_hex((dst >> 16) & 0xFF,
			(dst >> 8) & 0xFF, (dst) & 0xFF, (dst >> 24) & 0xFF);
	return (color);
}

void draw_texture(t_play *game, t_rayc *ray, int num)
{
	int			y;
	t_img		sprite;
	uint32_t	color;

	y = -1;
	sprite = get_sprite(game, ray);
	ray->text_x = (int)(ray->wall_x * (double)sprite.width);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
		ray->text_x = sprite.width - ray->text_x - 1;
	ray->next = 1.0 * sprite.height / ray->line;
	ray->sprite_start = (ray->start - WIN_HEIGHT / 2 + ray->line / 2) * ray->next;
	printf("llego aquii 111111\n");

	printf("%d\n", ray->start);
	printf("%d\n", ray->end);
	while (y < ray->start)
	// 	pixel_put(frame, num, y, SKY);
		y++;
	while(y <= ray->end)
	{
		ray->text_y = (int)ray->sprite_start;
		// ray->text_y = (double)ray->sprite_start + ray->next;
		ray->sprite_start += ray->next;
		// printf("111111111\n");
		// // ray->text_y = (int)ray->sprite_start & (sprite.height - 1);
		// printf("2222222222\n");
		color = pixel_get(&sprite, ray->text_x, ray->text_y);
		printf("33333333333\n");
		pixel_put(&game->raycast, num, y, color);
		// sprite_pixel_put(game->raycast, num, y, color);
		y++;
	}
	while (y < WIN_HEIGHT)
	// {
	// 	pixel_put(frame, num, y, FLOOR);
		y++;	
	// }
	printf("llego aqui\n");
}

void get_frame_height(t_play *game, t_rayc *ray)
{
	if (ray->side == 0)
	{
		ray->wall_dist = ray->side_dist_x - ray->delta_dist_x;
		ray->wall_x = game->player.y + ray->wall_dist * ray->dir_y;
	}
	else
	{
		ray->wall_dist = ray->side_dist_y - ray->delta_dist_y;
		ray->wall_x = game->player.x + ray->wall_dist * ray->dir_x;
	}
	ray->wall_x -= floor(ray->wall_x);
	ray->line = (int)(WIN_HEIGHT / ray->wall_dist);
	ray->start = -ray->line / 2 + WIN_HEIGHT / 2;
	if (ray->start < 0)
		ray->start = 0;
	ray->end = ray->line / 2 + WIN_HEIGHT / 2;
	if (ray->end >= WIN_HEIGHT)
		ray->end = WIN_HEIGHT - 1;
}

t_rayc	init_ray(t_play *game, int frame)
{
	t_rayc	ray;

	ray.view = (2 * frame) / (double)WIN_WIDTH - 1;
	ray.dir_x = game->player.dir.x + game->player.plane.x * ray.view;
	ray.dir_y = game->player.dir.y + game->player.plane.y * ray.view;
	ray.map_x = (int)game->player.x;
	ray.map_y = (int)game->player.y;
	if (ray.dir_x == 0)
		ray.delta_dist_x = 1e30;
	else
		ray.delta_dist_x = fabs(1 / ray.dir_x);
	if (ray.dir_y == 0)
		ray.delta_dist_y = 1e30;
	else
		ray.delta_dist_y = fabs(1 / ray.dir_y);
	ray.coll = 0;
	ray.side = 0;
	if (ray.dir_x < 0)
	{
		ray.step_x = -1;
		ray.side_dist_x = (game->player.x - ray.map_x) * ray.delta_dist_x;
	}
	else
	{
		ray.step_x = 1;
		ray.side_dist_x = (ray.map_x + 1.0 - game->player.x) * ray.delta_dist_x;
	}
	if (ray.dir_y < 0)
	{
		ray.step_y = -1;
		ray.side_dist_y = (game->player.y - ray.map_y) * ray.delta_dist_y;
	}
	else
	{
		ray.step_y = 1;
		ray.side_dist_y = (ray.map_y + 1.0 - game->player.y) * ray.delta_dist_y;
	}
	return (ray);
}

t_img	init_draw(t_play *game)
{
	t_img	frame;

	mlx_clear_window(game->mlx, game->win);
	// frame.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	frame.width = WIN_WIDTH;
	frame.height = WIN_HEIGHT;
	// frame.data_addr = mlx_get_data_addr(frame.img, &frame.bpp, &frame.size_line, &frame.endian);
	return (frame);
}

void check_collision(t_play *game, t_rayc *ray)
{
	while  (ray->coll == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map->map[(int)ray->map_y][(int)ray->map_x] == '1')
			ray->coll = 1;
	}
}

void do_walls(t_play *game)
{
	t_rayc	ray;
	int		num_frame;

	game->raycast = init_draw(game);
	num_frame = 0;
	while (num_frame < WIN_WIDTH)
	{
		ray = init_ray(game, num_frame);
		printf("%f\n", ray.view);
		printf("ray -> %f - %f\n", ray.dir_x, ray.dir_y);
		printf("side -> %f - %f\n", ray.side_dist_x, ray.side_dist_y);
		printf("\n");
		check_collision(game, &ray);
		get_frame_height(game, &ray);
		draw_texture(game, &ray, num_frame);
		printf("2222222222\n");
		num_frame++;
	}
	// mlx_put_image_to_window(game->mlx, game->win, game->raycast.img, 0, 0);
	// mlx_destroy_image(game->mlx, frame.img);
}