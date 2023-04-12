/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:36:59 by mibernar          #+#    #+#             */
/*   Updated: 2023/04/12 18:04:27 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_elements(t_game *mlx, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && mlx->map_info.north == 0)
		mlx->map_info.north = 1;
	else if (ft_strncmp(line, "SO ", 3) == 0 && mlx->map_info.south == 0)
		mlx->map_info.south = 1;
	else if (ft_strncmp(line, "WE ", 3) == 0 && mlx->map_info.west == 0)
		mlx->map_info.west = 1;
	else if (ft_strncmp(line, "EA ", 3) == 0 && mlx->map_info.east == 0)
		mlx->map_info.east = 1;
	else if (ft_strncmp(line, "F ", 2) == 0 && mlx->map_info.floor == 0)
		mlx->map_info.floor = 1;
	else if (ft_strncmp(line, "C ", 2) == 0 && mlx->map_info.ceiling == 0)
		mlx->map_info.ceiling = 1;
	else
		return (0);
	return (1);
}

int	number_lines(int fd)
{
	int		linecount;
	int		readcount;
	int		line_size;
	char	c;	

	linecount = 1;
	line_size = 0;
	while (1)
	{
		readcount = read(fd, &c, 1);
		line_size += readcount;
		if (readcount == 0)
			break ;
		if (readcount < 0)
			return (-1);
		if (c == '\n')
			linecount++;
	}
	close(fd);
	return (linecount);
}

char	**get_map(int fd, char *path)
{
	char	**map;
	char	*line;
	int		i;
	int		nb_lines;

	nb_lines = number_lines(fd);
	map = malloc(sizeof(char *) * (nb_lines));
	if (map == NULL)
		return (NULL);
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		return (0);
	i = 0;
	map[i] = ft_strdup(line);
	while (line != NULL)
	{
		i++;
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		map[i] = malloc(sizeof(char) * (ft_strlen(line) + 1));
		map[i] = ft_strdup(line);
	}
	map[i] = NULL;
	return (map);
}

int	map_check(int fd, char *path, t_game *mlx)
{
	int	lines;
	int	i;

	mlx->map = get_map(fd, path);
	if (mlx->map == NULL)
		return (0);
	i = 0;
	lines = 0;
	while (mlx->map[i] != NULL && lines < 6)
	{
		// printf("line: %d %s\n", lines, mlx->map[i]);
		if (mlx->map[i][0] == '\n')
			i++;
		else
		{
			if (check_map_elements(mlx, mlx->map[i]) == 0)
				return (0);
			i++;
			lines++;
		}
	}
	return (1);
}
