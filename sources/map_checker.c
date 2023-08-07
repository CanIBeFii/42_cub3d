/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:28:13 by fialexan          #+#    #+#             */
/*   Updated: 2023/08/07 15:399:15 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_texture_path(char *line, t_game *mlx)
{
	char		*path;
	int			path_fd;
	int			line_len;
	int			x;

	x = 2;
	while (line[x] == ' ' || line[x] == '\t')
		x++;
	line_len = ft_strlen(line);
	if (line[line_len - 1] == '\n')
		path = ft_substr(line, x, line_len - x - 1);
	else
		path = ft_substr(line, x, line_len - x);
	path_fd = open(path, O_RDONLY);
	if (path_fd < 0)
		return (1);
	if (check_dup_textures(mlx, line) == 1)
		return (1);
	return (0);
}

int	check_rgb_values(char *line, t_game *mlx)
{
	char		**rgb_char;
	int			x;

	x = 1;
	while (line[x] == ' ' || line[x] == '\t')
		x++;
	rgb_char = ft_split(line + x, ',');
	if (rgb_char == NULL)
		return (1);
	mlx->rgb.r = ft_atoi(rgb_char[0]);
	mlx->rgb.g = ft_atoi(rgb_char[1]);
	mlx->rgb.b = ft_atoi(rgb_char[2]);
	if ((mlx->rgb.r < 0 || mlx->rgb.r > 255) || (mlx->rgb.g < 0 || mlx->rgb.g > 255)
		|| (mlx->rgb.b < 0 || mlx->rgb.b > 255) || rgb_char[3] != NULL)
		return (1);
	if (ft_strncmp(line, "C ", 2) == 0)
		get_ceiling_rgb_values(&mlx.info);
	else if (ft_strncmp(line, "F ", 2) == 0)
		get_floor_rgb_values(&mlx.info);
	return (0);
}

int	check_info(char *line, t_game *mlx)
{
	if (check_missing_info(mlx) == 0)
		return (2);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
	{
		if (check_texture_path(line, mlx) == 1)
			return (1);
	}
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
	{
		if (check_rgb_values(line, mlx) == 1)
			return (1);
	}
	else
		return (1);
	return (0);
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

char *go_to_first_map_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL && ft_strcmp(line, "\n") == 0)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

int	get_map(int fd, t_map *map)
{
	char	*line;
	int		index;

	line = go_to_first_map_line(fd);
	index = 0;
	while (line != NULL)
	{
		if (check_map_line(line) == 0)
		{
			free_double_array(map->map);
			return (0);
		}
		map->map = realloc_double_char_array(map->map);
		map->map[index] = ft_substr(line, 0, ft_strlen(line) - 1);
		index++;
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

void	map_checker(char *path, t_game *mlx)
{
	int			fd;

	fd = open(path, O_RDONLY);
	if (get_map_info(fd, mlx) == 1)
	{
		perror("Error: invalid map given");
		exit(1);
	}
	get_map(fd, &mlx->map);
	if (mlx->map == NULL)
	{
		perror("Error: invalid map given");
		//Free stuff
		exit(1);
	}
}
