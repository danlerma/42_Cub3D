/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:02:02 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/11/23 15:46:16 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<cub3d.h>
#include"game.h"

int	endian(void)
{
	int16_t	i;
	int8_t	*p;

	i = 1;
	p = (int8_t *) &i;
	if (p[0] == 1)
		return (1);
	else
		return (0);
}

static void	cond_endian(t_play *game, int pixel, int color)
{
	if (game->minimap.endian == 1)
	{
		game->minimap.data_addr[pixel] = color >> 24;
		game->minimap.data_addr[pixel + 1] = (color >> 16) & 0xFF;
		game->minimap.data_addr[pixel + 2] = (color >> 8) & 0xFF;
		game->minimap.data_addr[pixel + 3] = color & 0xFF;
	}
	else
	{
		game->minimap.data_addr[pixel] = color & 0xFF;
		game->minimap.data_addr[pixel + 1] = (color >> 8) & 0xFF;
		game->minimap.data_addr[pixel + 2] = (color >> 16) & 0xFF;
		game->minimap.data_addr[pixel + 3] = color >> 24;
	}
}

static void	draw_colors(t_play *game, int color)
{
	int	x;
	int	y;
	int	pixel;

	y = 0;
	while (y < game->minimap.height)
	{
		x = 0;
		while (x < game->minimap.width)
		{
			pixel = (x * 4) + (y * game->minimap.size_line);
			cond_endian(game, pixel, color);
			x++;
		}
		y++;
	}
}

void	minimap(t_play *game)
{
	game->minimap.img = mlx_new_image(game->mlx, game->minimap.width,
			game->minimap.height);
	game->minimap.data_addr = mlx_get_data_addr(game->minimap.img,
			&game->minimap.bpp, &game->minimap.size_line,
			&game->minimap.endian);
	draw_colors(game, BACK);
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, 0, 0);
}
