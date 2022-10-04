#include <cub3d.h>

void leaks(void)
{
	system("leaks -q cub3D\n");
}

int	main(int argc, char** argv)
{
	t_map	*map;

	atexit(leaks);
	if (argc != 2)
		error_exit("Wrong arguments");
	map = checkmap(argv[1]);
	free_map(&map);
	return (0);
}
