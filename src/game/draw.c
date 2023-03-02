#include <cub3d.h>

// void	draw_line(t_img img, t_coord orig, t_coord end, int texture)
// {
// 	float	step_x;
// 	float	step_y;
// 	float	dist;
// 	int		i;

// 	dist = sqrt(pow(orig.x - end.x, 2)
// 			+ pow(bres.y - bres.end_y, 2));
// 	step_x = (bres.end_x - bres.x) / dist;
// 	step_y = (bres.end_y - bres.y) / dist;
// 	i = 0;
// 	while (i < dist)
// 	{
// 		my_mlx_pixel_put(&img, (bres.x + step_x * i), 
// 			(bres.y + step_y * i), texture);
// 		i++;
// 	}
// }
