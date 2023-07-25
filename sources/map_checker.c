/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:28:13 by fialexan          #+#    #+#             */
/*   Updated: 2023/07/25 17:35:27 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_texture_path(char *line)
{
	t_map_info	textures;
	char		*path;
	int			path_fd;
	int			line_len;
	int			x;

	x = 2;
	while (path[x] == ' ' || path[x == '\t'])
		x++;
	line_len = ft_strlen(line);
	path = ft_substr(line, x, line_len - x);
	path_fd = open(path, O_RDONLY);
	if (path_fd < 0)
		return (1);
	if (ft_strncmp(line, "NO ", 3) == 0)
		textures.north_texture = path_fd;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		textures.south_texture = path_fd;
	else if (ft_strncmp(line, "EA ", 3) == 0)	
		textures.east_texture = path_fd;
	else
		textures.west_texture = path_fd;
	return (0);
}

int	check_rgb_values(char *line)
{
	t_map_info	color;
	char		**rgb;
	int			x;

	x = 1;
	while (line[x] == ' ' || line[x == '\t'])
		x++;
	rgb = ft_split(line + x, ',');
	if ((rgb[0] < 0 || rgb[0] > 255) || (rgb[1] < 0 || rgb[1] > 255)
		|| (rgb[2] < 0 || rgb[2] > 255) || rgb[3] != NULL)
		return (1);
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		color.ceiling_color.r = rgb[0];
		color.ceiling_color.g = rgb[1];
		color.ceiling_color.b = rgb[2];

	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		color.floor_color.r = rgb[0];
		color.floor_color.g = rgb[1];
		color.floor_color.b = rgb[2];
	}
	return (0);
}

int	check_info(char *line)
{
	if (ft_strncmp(line, "NO ", 3) != 0 && ft_strncmp(line, "SO ", 3) != 0 &&
		ft_strncmp(line, "WE ", 3) != 0 && ft_strncmp(line, "EA ", 3) != 0)
	{
		if (check_texture_path(line) == 1)
			return (1);
	}
	else if (ft_strncmp(line, "F ", 2) != 0 && ft_strncmp(line, "C ", 2) != 0)
	{
		if (check_rgb_values(line) == 1)
			return (1);
	}
	else
		return (1);
	return (0);
}

void	get_map_info(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
		return ;
	while (line != NULL)
	{
		if (line[0] == '\n')
			continue ;
		else if (check_info(line) == 1)
			return (1);
		line = get_next_line(fd);
	}
}

t_map	*get_map(int fd, t_map_info *info)
{
	char	*line;
	t_map	*map;
	int		index;

	map = malloc(sizeof(t_map) * 1);
	if (map == NULL)
		return (NULL);
	line = get_next_line(fd);
	index = 0;
	while (line != NULL)
	{
		map->map = realloc_double_char_array(map->map);
		if (not_valid_map_line(line) == 1)
		{
			free_map(map);
			return (NULL);
		}
		map->map[index] = ft_strdup(line);
		index++;
		free(line);
		line = get_next_line(fd);
	}
	return (map);
}

void	map_checker(char *path)
{
	int			fd;
	t_map_info	*info;
	t_map		*map;

	fd = open(path, O_RDONLY);
	info = get_map_info(fd);
	if (info == NULL)
	{
		perror("Error: invalid map given");
		exit(1);
	}
	map = get_map(fd, info);
	if (map == NULL)
	{
		perror("Error: invalid map given");
		//Free stuff
		exit(1);
	}

}