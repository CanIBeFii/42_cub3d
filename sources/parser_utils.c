/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:38:56 by fialexan          #+#    #+#             */
/*   Updated: 2023/05/15 16:39:29 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_file(char *path)
{
	int	fd;

	if (check_file_type(path) == 0)
		return (0);
	fd = open(path, O_RDONLY);
	return (fd);
}

int	check_file_type(char *path)
{
	int	size;

	size = ft_strlen(path) - 1;
	return (path[size] == 'b' && path[size - 1] == 'u'
		&& path[size - 2] == 'c' && path[size - 3] == '.');
}
