/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:21:35 by canibefii         #+#    #+#             */
/*   Updated: 2023/05/29 17:47:56 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_map	*parser(char *path)
{
	int			fd;
	t_map_info	map_info;

	fd = is_valid_file(path);
	if (fd == -1)
		return (NULL);
}

t_map_info	get_map_info(int fd)
{
	t_map_info	info;
	char		*line;

	line = get_next_line(fd);
	while (has_all_info(info) == 0)
	{
		if (is_possible_line(line) == 1)
		{
			assign_path_to_info(info, line);
		}
		free(line);
		line = get_next_line(fd);
	}
}

void	assign_path_to_info(t_map_info info, char *line)
{
	int	iter;

	iter = 1;
	if (line[iter] != ' ')
		iter += 1;
	while (line[iter] == ' ')
		iter += 1;
	if (ft_strncmp("NO", line, 2) == 0)
		
}

int	is_possible_line(char *line)
{
	return (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0
		|| ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0);
}

int	has_all_info(t_map_info info)
{
	if (info.north_texture == NULL && info.south_texture == NULL
		&& info.east_texture == NULL && info.west_texture == NULL)
		return (0);
	if (info.sky_color == 0 && info.ground_color == 0)
		return (0);
	return (1);
}
