/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:28:13 by fialexan          #+#    #+#             */
/*   Updated: 2023/08/16 16:27:45 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_checker(char *path, t_game *mlx)
{
	int			fd;

	fd = open(path, O_RDONLY);
	if (get_map_info(fd, mlx) == 1)
		exit(1);
	// get_map(fd, &mlx->map);
	// if (mlx->map.map == NULL)
	// {
	// 	perror("Error: invalid map given");
	// 	//Free stuff
	// 	exit(1);
	// }
	// validate_map(&mlx->map);
}

int	get_map_info(int fd, t_game *mlx)
{
	char	*line;
	int		return_value;

	line = get_next_line(fd);
	if (line == NULL)
		return (1);
	while (line != NULL)
	{
		if (line[0] == '\n')
			;
		else
		{
			return_value = check_info(line, mlx);
			if (return_value == 1)
				return (1);
			else if (return_value == 2)
				break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	get_map(int fd, t_map *map)
{
	char	*line;
	int		index;
	int		max_line_size;

	line = go_to_first_map_line(fd);
	index = 0;
	max_line_size = 0;
	while (line != NULL)
	{
		if (check_map_line(line) == 0)
		{
			free_double_array(map->map);
			return (0);
		}
		if ((int)ft_strlen(line) > max_line_size)
			max_line_size = ft_strlen(line);
		map->map = realloc_double_char_array(map->map, max_line_size);
		map->map[index] = ft_substr(line, 0, ft_strlen(line) - 1);
		index++;
		free(line);
		line = get_next_line(fd);
	}
	map->x = max_line_size;
	map->y = index;
	return (1);
}
