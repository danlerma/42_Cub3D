/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:17:51 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/11/22 16:18:38 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<cub3d.h>

static int	index_to_base(char c, int base_len, char *base)
{
	int	i;

	i = 0;
	while (i < base_len)
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

unsigned long	ft_atoi_base(char *str, char *base)
{
	int				i;
	int				base_len;
	unsigned long	num;

	base_len = ft_strlen(base);
	i = 0;
	if (str[i] == 48 && str[i + 1] == 120)
		i++;
	num = 0;
	while (index_to_base(str[i], base_len, base) != -1)
	{
		num = num * base_len + index_to_base(str[i], base_len, base);
		i++;
	}
	return (num);
}
