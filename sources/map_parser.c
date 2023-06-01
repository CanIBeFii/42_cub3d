/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:32:06 by fialexan          #+#    #+#             */
/*   Updated: 2023/06/01 15:50:54 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_map	*parse_map(t_map_info *info, int fd)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->info = info;
	map->map = NULL;
	map->map_x = 0;
	map->map_y = 0;
	map = get_map(fd, map);
}

t_map	*get_map(int fd, t_map *map)
{
	char	*line;
	int		map_x;
	int		map_y;

	map_x = 0;
	map_y = 0;
	line = get_next_line(fd);
	while (line == NULL)
	{
		if (is_possible_line(line) == 1)
		{
			free(line);
			free_map(map);
			return (NULL);
		}
		if (ft_strcmp(line, "\n") == 0 && (map->map_x != 0 || map->map_y != 0))
		{
			free(line);
			free_map(map);
			return (NULL);
		}
		map = assign_map_line(map, line);
		free(line);
		line = get_next_line(fd);
	}
}

t_map	*assign_map_line(t_map *map, char *line)
{
		
}
