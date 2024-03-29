/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:28:13 by fialexan          #+#    #+#             */
/*   Updated: 2023/09/06 17:52:13 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_checker(char *path, t_game *mlx)
{
	int			fd;

	fd = open(path, O_RDONLY);
	if (get_map_info(fd, mlx) == 1)
	{
		free_game(mlx);
		exit(1);
	}
	if (get_map(fd, &mlx->map, 0, 0) == 0)
	{
		mlx->map.map = NULL;
		free_game(mlx);
		exit(1);
	}
	if (validate_map(&mlx->map) == 0)
	{
		free_game(mlx);
		exit(1);
	}
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
	if (line)
		free (line);
	return (0);
}

int	get_map(int fd, t_map *map, int index, int max_line_size)
{
	char	*line;

	line = go_to_first_map_line(fd);
	while (line != NULL)
	{
		if (check_map_line(line) == 0)
		{
			free_double_array(map->map);
			return (print_error("Error: invalid map line", 0));
		}
		if ((int)ft_strlen(line) > max_line_size)
			max_line_size = ft_strlen(line);
		map->map = realloc_double_char_array(map->map, max_line_size, 0);
		if (ft_strchr(line, '\n') != NULL)
			map->map[index++] = ft_substr(line, 0, ft_strlen(line) - 1);
		else
			map->map[index++] = ft_substr(line, 0, ft_strlen(line));
		free (line);
		line = get_next_line(fd);
	}
	map->max_x = max_line_size;
	map->max_y = index;
	return (1);
}
