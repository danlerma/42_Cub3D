/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:19:15 by pdel-pin          #+#    #+#             */
/*   Updated: 2023/06/05 18:44:45 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_img	get_sprite(t_play *game, t_rayc *ray)
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

void	draw_texture(t_play *game, t_rayc *ray, int num)
{
	int			y;
	t_img		sprite;
	uint32_t	color;

	sprite = get_sprite(game, ray);
	ray->text_x = (int)(ray->wall_x * (double)sprite.width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		ray->text_x = sprite.width - ray->text_x - 1;
	ray->next = 1.0 * sprite.height / ray->line;
	ray->sprite_start = (ray->start - WIN_HEIGHT / 2
			+ ray->line / 2) * ray->next;
	y = -2;
	while (++y < ray->start + 1)
		pixel_put(&game->raycast, num, y, game->map->sky);
	while (y <= ray->end)
	{
		ray->text_y = (int)ray->sprite_start;
		ray->sprite_start += ray->next;
		color = pixel_get(&sprite, sprite.width - ray->text_x - 1, ray->text_y);
		pixel_put(&game->raycast, num, y, color);
		y++;
	}
	while (y++ < WIN_HEIGHT)
		pixel_put(&game->raycast, num, y - 1, game->map->floor);
}
