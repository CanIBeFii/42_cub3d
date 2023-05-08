/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:36:59 by mibernar          #+#    #+#             */
/*   Updated: 2023/05/08 12:09:07 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_content(t_game *mlx)
{
	int	x;
	int	i;
	int	start;

	start = mlx->map_info.last_line_info_elem;
	i = start;
	while (mlx->map[i] && mlx->map[i][0] == '\n')
		i++;
	if (mlx->map[i] == NULL)
		return (0);
	mlx->map_info.map_x = ft_strlen(mlx->map[i]) - 1;
	while (mlx->map[i])
	{
		x = 0;
		while (mlx->map[i][x])
		{
			if (check_map_characters(mlx->map[i][x]) == 0)
			{
				printf("%s\n", mlx->map[i]);
				return (0);
			}
			if (mlx->map[i][x] == 'N')
			{
				mlx->player.pos_x = x * 64 + 32;
				mlx->player.pos_y = (i - start - 1) * 64 + 32;
			}
			x++;
		}
		i++;
	}
	mlx->map_info.map_y = i - start - 1;
	return (1);
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
		// printf("line: %d %s\n	", lines, mlx->map[i]);
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
	if (lines < 6)
		return (0);
	mlx->map_info.last_line_info_elem = i;
	if (check_map_content(mlx) == 0)
		return (0);
	return (1);
}
