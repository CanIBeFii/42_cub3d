/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:43:48 by fialexan          #+#    #+#             */
/*   Updated: 2023/08/18 16:29:10 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (check_rgb_values(line, &mlx->info) == 1)
			return (1);
	}
	else
	{
		perror("Error: not enough information given\n");
		return (1);
	}
	if (check_missing_info(&mlx->info) == 0)
		return (2);
	return (0);
}

int	check_rgb_values(char *line, t_map_info *info)
{
	char	**rgb_char;
	t_rgb	rgb;
	int		x;

	x = 1;
	while (line[x] == ' ' || line[x] == '\t')
		x++;
	rgb_char = ft_split(line + x, ',');
	if (rgb_char == NULL)
		return (1);
	if (double_array_size(rgb_char) != 3)
	{
		free_double_array(rgb_char);
		perror("Error: invalid number of rgb values given\n");
		return (1);
	}
	if (check_values(rgb_char) == 0)
	{
		free_double_array(rgb_char);
		perror("Error: rgb values must be integers\n");
		return (1);
	}
	rgb.r = ft_atoi(rgb_char[0]);
	rgb.g = ft_atoi(rgb_char[1]);
	rgb.b = ft_atoi(rgb_char[2]);
	if ((rgb.r < 0 || rgb.r > 255) || (rgb.g < 0 || rgb.g > 255)
		|| (rgb.b < 0 || rgb.b > 255))
	{
		free_double_array(rgb_char);
		perror("Error: rgb value out of bounds\n");
		return (1);
	}
	free_double_array(rgb_char);
	if (ft_strncmp(line, "C ", 2) == 0)
		get_rgb_values(&info->ceiling_color, rgb);
	else if (ft_strncmp(line, "F ", 2) == 0)
		get_rgb_values(&info->floor_color, rgb);
	return (0);
}

int	check_values(char **rgb_char)
{
	int	x;
	int	y;

	x = 0;
	while (rgb_char[x] != NULL)
	{
		y = 0;
		while (rgb_char[x][y] != '\0' && rgb_char[x][y] != '\n')
		{
			if (ft_isdigit(rgb_char[x][y]) == 0)
			{
				return (0);
			}
			y++;
		}
		x++;
	}
	return (1);
}

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
	free (path);
	if (path_fd < 0)
	{
		perror("Error: texture not found\n");
		return (1);
	}
	if (check_dup_textures(mlx, line) == 1)
	{
		perror("Error: duplicate texture found\n");
		return (1);
	}
	return (0);
}