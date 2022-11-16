/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:32:30 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/11/16 15:15:59 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<cub3d.h>

void	check_textures(char *texture, char *name, char *check)
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

void	check_colors(char *color, char *name, char *check)
{
	if ((check != NULL && *check != '\n') || ft_strlen(name) > 1)
		error_exit("Wrong colors.");
	(void)color;
	(void)name;
}
