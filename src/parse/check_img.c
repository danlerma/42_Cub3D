/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:32:30 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/11/22 16:15:54 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<cub3d.h>

static void	check_textures(char *texture, char *name, char *check)
{
	char	*ext;

	if ((check != NULL && *check != '\n') || ft_strlen(name) > 2)
		error_exit("Wrong textures.");
	if (open(texture, O_RDONLY) == -1)
		error_exit("Opening textures.");
	ext = ft_strrchr(texture, '.');
	if (ext == NULL || ft_strncmp(ext, ".xpm", ft_strlen(texture)) != 0)
		error_exit("Invalid format.");
}

static int	check_numbers(char **colors, t_parse *parse)
{
	int	i;
	int	y;

	i = 0;
	while (colors[i])
	{
		y = 0;
		while (colors[i][y])
		{
			if (ft_isdigit(colors[i][y]) == 0)
				error_exit("Character in the color.");
			y++;
		}
		parse->color[i] = ft_atoi(colors[i]);
		if (parse->color[i] > 255 || parse->color[i] == -1)
			error_exit("Up or down number.");
		i++;
	}
	if (i != 3)
		error_exit("Wrong number of colors.");
	return (transform_numbers(parse));
}

static int	check_colors(char *color, char *name, char *chk, t_parse *parse)
{
	char	**colors;
	char	*point;
	int		nbr;

	if ((chk != NULL && *chk != '\n') || ft_strlen(name) > 1 || color[0] == ',')
		error_exit("Wrong colors.");
	colors = ft_split(color, ',');
	if (colors == NULL)
		error_exit("Failed doing split.");
	point = ft_strrchr(color, ',');
	if (point[1] == '\0')
		error_exit("Es distinto a null");
	nbr = check_numbers(colors, parse);
	ft_free_malloc(colors);
	return (nbr);
}

char	*assing_walls(char *line, int check)
{
	char	**split;
	char	*aux;

	if (check == -1)
		ft_print_errors("Same data\n.");
	split = ft_split(line, ' ');
	if (ft_strchr(split[1], '\n'))
		aux = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
	else
		aux = ft_strdup(split[1]);
	check_textures(aux, split[0], split[2]);
	ft_free_malloc(split);
	return (aux);
}

int	assing_colors(char *line, t_parse *parse, int check)
{
	char	**split;
	char	*aux;
	int		nbr;

	if (check == -1)
		ft_print_errors("Same data.\n");
	split = ft_split(line, ' ');
	if (ft_strchr(split[1], '\n'))
		aux = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
	else
		aux = ft_strdup(split[1]);
	nbr = check_colors(aux, split[0], split[2], parse);
	ft_free_malloc(split);
	free(aux);
	return (nbr);
}
