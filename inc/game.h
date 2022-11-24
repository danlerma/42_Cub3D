#ifndef GAME_H

# define GAME_H

# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define MINI_MAP 200
# define PLAYER 0xC00DFC
# define BACK 0x434343
# define FRONT 0xC6C6C6

typedef struct s_keys
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	w;
	int	a;
	int	s;
	int	d;
}	t_keys;

typedef struct s_player
{
	float	x;
	float	y;
	float	dir;
	t_keys	*keys;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*data_addr;
	int		bpp;
	int		endian;
	int		size_line;
	int		width;
	int		height;
}	t_img;

typedef struct s_sprites
{
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
	int		floor;
	int		sky;
}	t_sprites;

typedef struct s_play
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_player	*player;
	t_sprites	sprites;
	t_img		background;
	t_img		minimap;

}	t_play;

// main_game.c
void	game(t_map *map);

// hooks.c
int		close_window(t_play *game);

//minimap.c
void	minimap(t_play *game);
int		endian(void);

#endif
