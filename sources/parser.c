/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:21:35 by canibefii         #+#    #+#             */
/*   Updated: 2023/05/31 18:51:58 by fialexan         ###   ########.fr       */
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

t_map_info	*get_map_info(int fd)
{
	t_map_info	info;
	char		*line;

	line = get_next_line(fd);
	while (has_all_info(info) == 0)
	{
		if (is_possible_line(line) == 1)
		{
			if (assign_path_to_info(info, line) == 0)
				return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (&info);
}

int	assign_path_to_info(t_map_info info, char *line)
{
	int	iter;

	iter = 1;
	if (line[iter] != ' ')
		iter += 1;
	while (ft_isspace(line[iter]) == 1)
		iter += 1;
	if (ft_strncmp("NO", line, 2) == 0 && info.north_texture == NULL)
		info.north_texture = ft_strdup(line + iter);
	else if (ft_strcmp("SO", line, 2) == 0 && info.south_texture == NULL)
		info.south_texture = ft_strdup(line + iter);
	else if (ft_strncmo("WE", line, 2) == 0 && info.west_texture == NULL)
		info.west_texture = ft_strdup(line + iter);
	else if (ft_strncmp("EA", line, 2) == 0 && info.east_texture == NULL)
		info.east_texture = ft_strdup(line + iter);
	else if (ft_strncmp("F", line, 1) == 0 && info.ground_color == 0)
		info.ground_color = str_to_color(line + iter);
	else if (ft_strncmp("C", line, 1) == 0 && info.sky_color == 0)
		info.sky_color = str_to_color(line + iter);
	else
		return (0);
	return (1);
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
