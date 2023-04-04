#ifndef GAME_H

# define GAME_H

// # define WIN_WIDTH 1920
// # define WIN_HEIGHT 1080
# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define SPEED 0.15 //0.05
# define ANGLE 0.0174533
# define ROT_ANGLE 0.15

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53

# define SCALE 1.5 // poner 5
# define TDMAP_FLOOR 13157810
# define TDMAP_WALL 5066061
# define TDMAP_PLAYER 13905262
# define TDMAP_RAYS 16381677

# define ANGLE_SIXTY 1.0472
# define ANGLE_THIRTY 0.523599

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

typedef struct s_pos
{
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
}	t_pos;


typedef struct s_coord
{
	float x;
	float y;
}	t_coord;

typedef struct s_player
{
	float	x;
	float	y;
	float	ang;
	t_coord	next;
	t_coord	dir;
	t_keys	keys;
	t_coord	plane;
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

typedef struct s_rayc
{
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		side;
	int		coll;
	int		line;
	int		start;
	int		end;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	view;
	double	dir_x;
	double	dir_y;
	double	wall_x;
	double	wall_y;
	int		text_x;
	int		text_y;
	double	wall_dist;
	double	next;
	double	sprite_start;
}	t_rayc;

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
	t_player	player;
	t_sprites	sprites;
	t_img		background;
	t_img		tdmap;		// eliminar después, solo para visualización de movimiento
	t_img		raycast;
}	t_play;

// main_game.c
void	do_game(t_map *map, t_play *game);

// hooks.c
int		close_window(t_play *game);
int		k_pressed(int key, t_play *game);
int		k_released(int key, t_play *game);

/* utils.c */
int	ft_double_len(char **str);

/* tdmap.c */
void draw_tdmap(t_play *game, t_img tdmap, t_map *map, t_player player);
void draw_player(t_play *game, t_img tdmap, t_player player, float tile);
void	pixel_put(t_img *img, int i, int j, int color);
void draw_background(t_img background, int floor, int sky);

/* init_game.c */
void	init_game(t_play *game, t_map *map);
t_sprites	get_sprites(t_play *game, t_map *map);
t_player	init_player(t_map *map);
t_keys	init_keys(void);

/* draw */
void do_walls(t_play *game);
void draw_line_ray(t_img tdmap, t_coord pos, t_coord coll, int color);

#endif
