/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:25:54 by dlerma-c          #+#    #+#             */
/*   Updated: 2022/11/22 15:07:17 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<cub3d.h>

static int	num_characters(unsigned int nb)
{
	int	i;

	i = 0;
	if (nb != 0)
	{
		if (nb < 0)
			i = i + 1;
		while (nb != 0)
		{
			nb = nb / 10;
			i++;
		}
	}
	else
		i = 1;
	return (i);
}

static char	*join_the_digits(char	**str, unsigned int cal, char *base)
{
	char	*aux;
	char	*str2;

	aux = *str;
	str2 = ft_calloc(sizeof(char), 1 + 1);
	if (str2 == NULL)
		return (NULL);
	ft_memcpy(str2, base + cal, 1);
	*str = ft_strjoin(*str, str2);
	free(str2);
	free(aux);
	if (*str == NULL)
		return (NULL);
	return (*str);
}

static char	*hex_char(unsigned int num, char *base)
{
	unsigned int	cal;
	char			*str;

	str = ft_calloc(sizeof(char), num_characters(num) + 1);
	if (str == NULL)
		return (NULL);
	cal = num;
	while (cal >= 16)
	{
		cal = num % 16;
		str = join_the_digits(&str, cal, base);
		cal = num / 16;
		num = cal;
	}
	str = join_the_digits(&str, cal, base);
	if (str == NULL)
		error_exit("Malloc failed.");
	return (str);
}

static char	*cond_hex(int y, char *hex)
{
	char	*aux;

	aux = (char *)ft_calloc(y + 1, sizeof(char));
	if (aux == NULL)
		error_exit("Malloc failed.");
	if (y == 1)
	{
		aux[0] = '0';
		aux[1] = hex[0];
	}
	else
	{
		aux[0] = hex[1];
		aux[1] = hex[0];
	}
	return (aux);
}

void	transform_numbers(t_parse *parse)
{
	char	*hex;
	char	*aux;
	int		y;
	int		i;

	i = 0;
	parse->hex = ft_strdup("");
	while (parse->color[i])
	{
		hex = hex_char(parse->color[i], UPPER_HEX);
		y = ft_strlen(hex);
		aux = cond_hex(y, hex);
		free(parse->hex);
		parse->hex = ft_strjoin(parse->hex, aux);
		free(hex);
		free(aux);
		i++;
	}
}

// static int	ft_isspace(int c)
// {
// 	if (c == '\t' || c == '\n' || c == '\v'
// 		|| c == '\f' || c == '\r' || c == ' ')
// 		return (1);
// 	return (0);
// }

// static int	index_to_base(char c, int base_len, char *base)
// {
// 	int	i;

// 	i = 0;
// 	while (i < base_len)
// 	{
// 		if (base[i] == c)
// 			return (i);
// 		i++;
// 	}
// 	return (0);
// }

// unsigned long	ft_atoi_base(char *str, char *base)
// {
// 	int				i;
// 	int				base_len;
// 	unsigned long	num;

// 	base_len = ft_strlen(base);
// 	if (base_len != 16)
// 		print_error();
// 	i = 0;
// 	while (str[i])
// 	{
// 		str[i] = ft_tolower(str[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (ft_isspace(str[i]) != 0)
// 		i++;
// 	if (str[i] == 48 && str[i + 1] == 120)
// 		i += 2;
// 	num = 0;
// 	while (index_to_base(str[i], base_len, base) != 0)
// 	{
// 		num = num * base_len + index_to_base(str[i], base_len, base);
// 		i++;
// 	}
// 	return (num);
// }
