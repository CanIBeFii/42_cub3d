/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:50:55 by fialexan          #+#    #+#             */
/*   Updated: 2023/08/24 15:06:35 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_map(t_map *map)
{
	int		y;
	int		x;
	int		num_of_players;

	y = -1;
	num_of_players = 0;
	if (map->max_x == 0 || map->max_y == 0)
		return (print_error("Error: no map given\n", 0));
	while (map->map[++y] != NULL)
	{
		x = 0;
		while (map->map[y][x] != '\0')
		{
			if (is_inside_map_char(map->map[y][x]) == 1
				&& map->map[y][x] != '0')
				num_of_players += save_player_pos(&map->player, y,
						x, map->map[y][x]);
			if (check_surroundings(map, x, y) == 0)
				return (print_error("Error: invalid map\n", 0));
			x++;
		}
	}
	if (num_of_players != 1)
		return (print_error("Error: invalid map\n", 0));
	return (1);
}

int	check_surroundings(t_map *map, int x, int y)
{
	if (x == 0 || x == map->max_x || y == 0 || y == map->max_y)
	{
		if (is_inside_map_char(map->map[y][x]) == 0)
			return (1);
		return (0);
	}
	if (map->map[y][x] == '1' || map->map[y][x] == ' ')
		return (1);
	if (is_out(map, y - 1, x - 1) == 1 || is_out(map, y - 1, x) == 1
		|| is_out(map, y - 1, x + 1) == 1)
		return (0);
	if (is_out(map, y, x - 1) == 1 || is_out(map, y, x + 1) == 1)
		return (0);
	if (is_out(map, y + 1, x - 1) == 1 || is_out(map, y + 1, x) == 1
		||is_out(map, y + 1, x + 1) == 1)
		return (0);
	return (1);
}

int	is_out(t_map *map, int y, int x)
{
	if (map->map[y][x] == '\0' || map->map[y][x] == ' ')
		return (1);
	return (0);
}

int	is_inside_map_char(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}
