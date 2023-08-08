/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:50:55 by fialexan          #+#    #+#             */
/*   Updated: 2023/08/08 15:57:15 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_surroundings(char **map, int x, int y)
{
	if (x == 0)
		reuturn (0)
	// if (map[y + 1][x] == ' ' || map[y - 1][x] == ' ')
	// 	return (0);
	// else if (map[y][x + 1] == ' ' || map[y][x - 1] == ' ')
	// 	return (0);
	return (1);
}

int	check_valid_map(t_map *map)
{
	int		y;
	int		x;
	char	c;

	map->x = 0;
	y = 0;
	x = -1;
	while (map->map[0][++x] != '\0')
	{
		if (map->map[0][x] != '1' || map->map[0][x] != ' ')
			return (0);
	}
	while (map->map[++y + 1] != NULL)
	{
		x = 0;
		if (map->map[y][0] == '0')
			return (0);
		while (map->map[y][++x + 1] != '\0')
		{
			c = map->map[y][x];
			if (c == 0 && (check_surroundings(map->map, x, y) == 0))
				return (0);
		}
		if (map->map[y][x] == '0')
			return (0);
		if (map->x < x)
			map->x = x;
	}
	while (map->map[y][++x] != '\0')
	{
		if (map->map[y][x] == 0 || map->map[0][x] != ' ')
			return (0);
	}
	map->y = y;
	return (1);
}
