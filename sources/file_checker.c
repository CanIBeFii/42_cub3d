/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:21:58 by fialexan          #+#    #+#             */
/*   Updated: 2023/07/26 15:29:09 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file(int argc, char **argv, t_game *mlx)
{
	char	*path;
	int		fd;
	int		x;

	if (argc != 2)
	{
		perror("ERROR: invalid number of arguments");
		exit (1);
	}
	path = argv[1];
	x = ft_strlen(path) - 1;
	if (path[x] != 'b' || path[x - 1] != 'u' || path[x - 2] != 'c'
		|| path[x - 3] != '.')
	{
		perror("ERROR: invalid file type");
		exit (1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("ERROR: can't open file");
		exit (1);
	}
	mlx->path = path;
	close(fd);
}
