/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:33:19 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/10/04 16:39:31 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_file(char *file, t_map *map)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("Something went wrong opening the file.");
	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		if (ft)
		printf("%s", line);
		line = get_next_line(fd);
	}
	printf("\n");
	close(fd);
}
