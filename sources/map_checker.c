/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:28:13 by fialexan          #+#    #+#             */
/*   Updated: 2023/07/28 17:44:03 by mibernar         ###   ########.fr       */
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
	if (ft_strncmp(line, "NO ", 3) == 0)
		mlx->info.north_texture = path_fd;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		mlx->info.south_texture = path_fd;
	else if (ft_strncmp(line, "EA ", 3) == 0)	
		mlx->info.east_texture = path_fd;
	else
		mlx->info.west_texture = path_fd;
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
	{
		mlx->info.ceiling_color.r = mlx->rgb.r;
		mlx->info.ceiling_color.g = mlx->rgb.g;
		mlx->info.ceiling_color.b = mlx->rgb.b;
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		mlx->info.floor_color.r = mlx->rgb.r;
		mlx->info.floor_color.g = mlx->rgb.g;
		mlx->info.floor_color.b = mlx->rgb.b;
	}
	return (0);
}

int	check_info(char *line, t_game *mlx)
{
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
	{
		if (mlx->info.east_texture == -1 || mlx->info.west_texture == -1
			|| mlx->info.north_texture == -1 || mlx->info.south_texture == -1
			|| mlx->info.ceiling_color.r == -1 || mlx->info.ceiling_color.g == -1
			|| mlx->info.ceiling_color.b == -1 || mlx->info.floor_color.r == -1
			|| mlx->info.floor_color.g == -1 || mlx->info.floor_color.b == -1)
			return (1);
		return (2);
	}
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
			printf("%d\n", return_value);
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

void	get_map(int fd, t_game *mlx)
{
	char	*line;
	int		index;

	mlx->map = malloc(sizeof(t_map) * 1);
	if (mlx->map == NULL)
		return ;
	line = get_next_line(fd);
	index = 0;
	while (line != NULL)
	{
		mlx->map->map = realloc_double_char_array(mlx->map->map);
		// if (not_valid_map_line(line) == 1)
		// {
		// 	free_map(map);
		// 	return (NULL);
		// }
		mlx->map->map[index] = ft_strdup(line);
		index++;
		free(line);
		line = get_next_line(fd);
	}
}

void	map_checker(char *path, t_game *mlx)
{
	int			fd;
	int			x = 0;

	fd = open(path, O_RDONLY);
	if (get_map_info(fd, mlx) == 1)
	{
		perror("Error: invalid map given");
		exit(1);
	}
	close(fd);
	fd = open(path, O_RDONLY);
	get_map(fd, mlx);
	if (mlx->map == NULL)
	{
		perror("Error: invalid map given");
		//Free stuff
		exit(1);
	}
	while (mlx->map->map[x] != NULL)
	{
		printf("%s\n", mlx->map->map[x]);
		x++;
	}
}
