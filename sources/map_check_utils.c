/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:20:43 by mibernar          #+#    #+#             */
/*   Updated: 2023/04/13 16:21:29 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	check_map_characters(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'W' && c != 'E'
		&& c != '\n' && c != ' ')
		return (0);
	return (1);
}