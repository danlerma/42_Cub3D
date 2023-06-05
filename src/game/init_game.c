/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:19:18 by pdel-pin          #+#    #+#             */
/*   Updated: 2023/06/05 17:57:07 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_keys	init_keys(void)
{
	t_keys	keys;

	keys.up = 0;
	keys.down = 0;
	keys.left = 0;
	keys.right = 0;
	keys.w = 0;
	keys.a = 0;
	keys.s = 0;
	keys.d = 0;
	return (keys);
}

void	def_dir(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
	}
	if (dir == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
	}
	if (dir == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
	}
	if (dir == 'W')
	{
		player->dir.x = 0;
		player->dir.y = 1;
	}
	player->plane.x = player->dir.y * -0.66;
	player->plane.y = player->dir.x * 0.66;
}

t_player	init_player(t_map *map)
{
	int			i;
	int			j;
	char		dir;
	t_player	player;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
			|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				player.x = (float)j + 0.5;
				player.y = (float)i + 0.5;
				dir = map->map[i][j];
			}
		}
	}
	def_dir(&player, dir);
	player.keys = init_keys();
	return (player);
}

t_sprites	get_sprites(t_play *game, t_map *map)
{
	t_sprites	s;

	s.north.img = mlx_xpm_file_to_image(game->mlx, map->nsew[3],
			&s.north.width, &s.north.height);
	s.south.img = mlx_xpm_file_to_image(game->mlx, map->nsew[2],
			&s.south.width, &s.south.height);
	s.east.img = mlx_xpm_file_to_image(game->mlx, map->nsew[1],
			&s.east.width, &s.east.height);
	s.west.img = mlx_xpm_file_to_image(game->mlx, map->nsew[0],
			&s.west.width, &s.west.height);
	s.north.data_addr = mlx_get_data_addr(s.north.img, &s.north.bpp,
			&s.north.size_line, &s.north.endian);
	s.south.data_addr = mlx_get_data_addr(s.south.img, &s.south.bpp,
			&s.south.size_line, &s.south.endian);
	s.east.data_addr = mlx_get_data_addr(s.east.img, &s.east.bpp,
			&s.east.size_line, &s.east.endian);
	s.west.data_addr = mlx_get_data_addr(s.west.img, &s.west.bpp,
			&s.west.size_line, &s.west.endian);
	s.floor = map->floor;
	s.sky = map->sky;
	return (s);
}

void	init_game(t_play *game, t_map *map)
{
	int	size;

	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	game->map = map;
	game->player = init_player(map);
	game->sprites = get_sprites(game, map);
	game->background.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->background.size_line = game->background.width
		* (game->background.bpp / 8);
	game->background.data_addr = mlx_get_data_addr(game->background.img,
			&game->background.bpp, &game->background.size_line,
			&game->background.endian);
	size = fmin(WIN_WIDTH / SCALE / ft_strlen(map->map[0]),
			WIN_HEIGHT / SCALE / ft_double_len(map->map));
	game->tdmap.width = size * ft_strlen(map->map[0]);
	game->tdmap.height = size * ft_double_len(map->map);
	game->tdmap.img = mlx_new_image(game->mlx, game->tdmap.width,
			game->tdmap.height);
	game->tdmap.size_line = game->tdmap.width * (game->tdmap.bpp / 8);
	game->tdmap.data_addr = mlx_get_data_addr(game->tdmap.img,
			&game->tdmap.bpp, &game->tdmap.size_line, &game->tdmap.endian);
}
