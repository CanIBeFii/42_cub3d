/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:07:47 by fialexan          #+#    #+#             */
/*   Updated: 2023/08/07 16:03:05 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_valid_map(t_map *map)
{
	int		y;
	int		x;
	char	c;

	map->x = 0;
	y = 1;
	x = 0;
	while (map->map[0][x] != '\0')
	{
		if (map->map[0][x] != '1' || map->map[0][x] != ' ')
			return (0);
		x++;
	}
	while (map->map[y + 1] != NULL)
	{
		x = 0;
		if (map->map[y][0] == '0')
			return (0);
		while (map->map[y][x + 1] != '\0')
		{
			c = map->map[y][x];
			if (c == 0 && (check_surroundings(map->map, x, y) == 0))
				return (0);
			x++;
		}
		if (map->map[y][x] == '0')
			return (0);
		if (map->x < x)
			map->x = x;
		y++;
	}
	while (map->map[y][x] != '\0')
	{
		if (map->map[y][x] == 0 || map->map[0][x] != ' ')
			return (0);
		x++;
	}
	map->y = y;
	return (1);
}

int	check_surroundings(char **map, int x, int y)
{
	if (map[y + 1][x] == ' ' || map[y - 1][x] == ' ')
		return (0);
	else if (map[y][x + 1] == ' ' || map[y][x - 1] == ' ')
		return (0);
	return (1);
}

char	**realloc_double_char_array(char **array)
{
	int		size;
	int		index;
	char	**new_array;

	index = 0;
	size = double_array_size(array);
	new_array = malloc(sizeof(char *) * (size + 2));
	if (new_array == NULL)
		return (NULL);
	while (index != size)
	{
		new_array[index] = ft_strdup(array[index]);
		free(array[index]);
		index++;
	}
	new_array[index] = NULL;
	new_array[index + 1] = NULL;
	free(array);
	return (new_array);
}

int check_map_line(char *line)
{
	int		index;
	char	c;

	index = 0;
	if (line == NULL || ft_strcmp(line, "\n") == 0)
		reutrn (0);
	while (line[index] != '\0' || line[index] != '\n')
	{
		c = line[index];
		if (c != '0' && c != '1' && c != 'N' && c != 'E'
			&& c != 'S' && c != 'W' && c != ' ')
			return (0);
		index += 1;
	}
	return (1);
}

int	double_array_size(char **array)
{
	int	size;

	size = 0;
	if (array == NULL)
		return (0);
	while (array[size] != NULL)
		size++;
	return (size);
}
