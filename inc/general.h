/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:08:38 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/10/04 12:08:38 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H

# define GENERAL_H

typedef struct s_map
{
	char	**map;
	char	**nsew;
	int		floor;
	int		sky;
	int		max_len;
}t_map;

#endif
