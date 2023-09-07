/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:43:48 by fialexan          #+#    #+#             */
/*   Updated: 2023/09/06 17:30:54 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_info(char *line, t_game *mlx)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
	{
		if (check_texture_path(line, mlx, 2) == 1)
		{
			free(line);
			return (1);
		}
	}
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
	{
		if (check_rgb_values(line, &mlx->info, 1) == 1)
		{
			free(line);
			return (1);
		}
	}
	else
	{
		free(line);
		return (print_error("Error: not enough information given\n", 1));
	}
	if (check_missing_info(&mlx->info) == 0)
		return (2);
	return (0);
}

int	check_rgb_values(char *line, t_map_info *info, int x)
{
	char	**rgb_char;
	t_rgb	rgb;

	while (line[x] == ' ' || line[x] == '\t')
		x++;
	rgb_char = ft_split(line + x, ',');
	if (rgb_char == NULL || double_array_size(rgb_char) != 3
		|| check_values(rgb_char) == 0)
	{
		free_double_array(rgb_char);
		return (print_error("Error: invalid rgb value given\n", 1));
	}
	if (assign_rgb_values(&rgb, rgb_char) == 1)
		return (print_error("Error: missing rgb value\n", 1));
	if ((rgb.r < 0 || rgb.r > 255) || (rgb.g < 0 || rgb.g > 255)
		|| (rgb.b < 0 || rgb.b > 255))
		return (print_error("Error: rgb value out of bounds\n", 1));
	if (check_dup_rgb(info, line[0]) == 1)
		return (print_error("Error: duplicate rgb value\n", 1));
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

	y = 0;
	while (rgb_char[y] != NULL)
	{
		x = 0;
		while (rgb_char[y][x] != '\0' && rgb_char[y][x] != '\n')
		{
			if (ft_isdigit(rgb_char[y][x]) == 0)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_texture_path(char *line, t_game *mlx, int x)
{
	char		*path;
	int			path_fd;
	int			line_len;

	while (line[x] == ' ' || line[x] == '\t')
		x++;
	line_len = ft_strlen(line);
	if (line[line_len - 1] == '\n')
		path = ft_substr(line, x, line_len - x - 1);
	else
		path = ft_substr(line, x, line_len - x);
	path_fd = open(path, O_RDONLY);
	if (path_fd < 0 || ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4) != 0)
	{
		free (path);
		return (print_error("Error: invalid texture\n", 1));
	}
	if (check_dup_textures(mlx, line, path) == 1)
	{
		free (path);
		return (print_error("Error: duplicate texture found\n", 1));
	}
	free (path);
	return (0);
}

int	assign_rgb_values(t_rgb *rgb, char **rgb_char)
{
	int	index;
	int	len;

	if (rgb_char[0] == NULL || rgb_char[1] == NULL || rgb_char[2] == NULL)
		return (1);
	index = -1;
	while (rgb_char[++index] != NULL)
	{
		len = -1;
		while (rgb_char[index][++len] != '\0')
		{
			if (ft_isdigit(rgb_char[index][len]) == 0
				&& rgb_char[index][len] != '\n')
				return (1);
		}
		if (len == 1 && rgb_char[index][0] == '\n')
			return (1);
	}
	rgb->r = ft_atoi(rgb_char[0]);
	rgb->g = ft_atoi(rgb_char[1]);
	rgb->b = ft_atoi(rgb_char[2]);
	free_double_array(rgb_char);
	return (0);
}
