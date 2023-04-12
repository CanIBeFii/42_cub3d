/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:32:28 by mibernar          #+#    #+#             */
/*   Updated: 2023/04/11 18:43:19 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include	<mlx.h>
# include "./libft.h"

typedef struct s_vector
{
	int	x;
	int	y;
}t_vector;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*window;
	t_vector	window_size;
	char		**map;
}t_game;

//MAIN.C
void	cub3d(int fd, char *path);

//WINDOW_MANAGEMENT.C
int		close_window(void);

//HANDLE_KEYS.C
int		keys(int keycode, t_game *mlx);

//MAP_CHECK.C
int		map_check(int fd, char *path, t_game *mlx);
char	**get_map(int fd, char *path);
int		number_lines(int fd);

//FREE.C
void	free_double_array(char **double_array);

#endif