/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:36:59 by mibernar          #+#    #+#             */
/*   Updated: 2023/04/11 18:40:57 by mibernar         ###   ########.fr       */
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

char	**get_map(int fd, char *path)
{
	char	**map;
	char	*line;
	int		i;
	int		nb_lines;

	nb_lines = number_lines(fd);
	map = malloc(sizeof(char *) * (nb_lines + 1));
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
		map[i] = ft_strdup(line);
	}
	map[i] = NULL;
	return (map);
}

int	map_check(int fd, char *path, t_game *mlx)
{
	mlx->map = get_map(fd, path);
	if (mlx->map == NULL)
		return (0);
	return (1);
}
