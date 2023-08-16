/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:50:55 by fialexan          #+#    #+#             */
/*   Updated: 2023/08/11 15:50:51 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_map(t_map *map)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (map->map[y] != NULL)
	{
		x = 0;
		while (map->map[y][x] != '\0')
		{
			if (check_surroundings(map, x, y) == 0)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_surroundings(t_map *map, int x, int y)
{
	if (x == 0 || x == map->x || y == 0 || y == map->y)
		return (is_inside_map_char(map->map[y][x]) == 0);
	return (1);
}

int	is_inside_map_char(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
