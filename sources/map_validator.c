/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:50:55 by fialexan          #+#    #+#             */
/*   Updated: 2023/08/16 18:29:52 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_map(t_map *map)
{
	int		y;
	int		x;

	y = 0;
	while (map->map[y] != NULL)
	{
		x = 0;
		while (map->map[y][x] != '\0')
		{
			if (check_surroundings(map, x, y) == 0)
			{
				perror("Error: invalid map");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_surroundings(t_map *map, int x, int y)
{
	if (x == 0 || x == map->x || y == 0 || y == map->y)
	{
		if (is_inside_map_char(map->map[y][x]) == 0)
			return (1);
		return (0);
	}
	if (map->map[y][x] == '1')
		return (1);
	if (map->map[y - 1][x - 1] == ' ' || map->map[y - 1][x] == ' '
		|| map->map[y + 1][x + 1] == ' ')
		return (0);
	if (map->map[y][x - 1] == ' ' || map->map[y][x + 1] == ' ')
		return (0);
	if (map->map[y + 1][x - 1] == ' ' || map->map[y + 1][x] == ' '
		|| map->map[y + 1][x + 1] == ' ')
		return (0);
	return (1);
}

int	is_inside_map_char(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}
