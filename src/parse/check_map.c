#include<cub3d.h>

static void	loop_blocks(char *row, int frt_lst)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (row[i])
	{
		if (row[i] == ' ' && flag == 0)
			i++;
		else if (frt_lst == 1)
		{
			flag = 1;
			if(row[i] != '1')
				error_exit("Walls are not closed.");
		}
		i++;
	}
}

void	check_map(t_map *map, t_parse *parse)
{
	printf("%d %d %d\n", parse->init_map, parse->num_map, parse->pos_map);
	parse->pos_map = 0;
	while (parse->pos_map < parse->num_map)
	{
		if (parse->pos_map == 0 || parse->pos_map == parse->num_map - 1)
			loop_blocks(map->map[parse->pos_map], 1);
		else
			loop_blocks(map->map[parse->pos_map], 0);
		parse->pos_map++;
	}
}
