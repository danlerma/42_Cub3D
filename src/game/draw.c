/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:10:43 by pdel-pin          #+#    #+#             */
/*   Updated: 2023/05/25 16:24:49 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_frame_height(t_play *game, t_rayc *ray)
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

static void	def_dir(t_play *game, t_rayc *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y)
			* ray->delta_dist_y;
	}
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
	def_dir(game, &ray);
	return (ray);
}

t_img	init_draw(t_play *game)
{
	t_img	frame;

	mlx_clear_window(game->mlx, game->win);
	frame.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	frame.width = WIN_WIDTH;
	frame.height = WIN_HEIGHT;
	frame.data_addr = mlx_get_data_addr(frame.img,
			&frame.bpp, &frame.size_line, &frame.endian);
	return (frame);
}

void	check_collision(t_play *game, t_rayc *ray)
{
	while (ray->coll == 0)
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
