/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:32:30 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/11/21 17:57:32 by dlerma-c         ###   ########.fr       */
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

static int	check_colors(char *color, char *name, char *check)
{
	if ((check != NULL && *check != '\n') || ft_strlen(name) > 1)
		error_exit("Wrong colors.");
	(void)color;
	(void)name;
	return (0);
}

char	*assing_walls(char *line)
{
	char	**split;
	char	*aux;

	split = ft_split(line, ' ');
	if (ft_strchr(split[1], '\n'))
		aux = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
	else
		aux = ft_strdup(split[1]);
	check_textures(aux, split[0], split[2]);
	ft_free_malloc(split);
	return (aux);
}

int	assing_colors(char *line)
{
	char	**split;
	char	*aux;
	int		nbr;

	split = ft_split(line, ' ');
	if (ft_strchr(split[1], '\n'))
		aux = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
	else
		aux = ft_strdup(split[1]);
	nbr = check_colors(aux, split[0], split[2]);
	ft_free_malloc(split);
	free(aux);
	return (nbr);
}
