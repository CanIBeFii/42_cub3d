/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:32:28 by mibernar          #+#    #+#             */
/*   Updated: 2023/04/14 17:50:35 by mibernar         ###   ########.fr       */
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
# include <math.h>
# include <mlx.h>
# include "./libft.h"

# define PI 3.1415926535

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	pdx;
	float	pdy;
	float	pa;
}t_player;

typedef struct s_map
{
	int	north;
	int	south;
	int	west;
	int	east;
	int	ceiling;
	int	floor;
	int	last_line_info_elem;
}t_map;

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
	t_map		map_info;
	t_player	player;
	char		**map;
}t_game;

//MAIN.C
void	cub3d(int fd, char *path);
void	game_init(t_game *mlx);
void	draw_square(t_game *mlx, int x, int y, int color);

//WINDOW_MANAGEMENT.C
int		close_window(t_game *mlx);

//HANDLE_KEYS.C
int		keys(int keycode, t_game *mlx);

//MAP_CHECK.C
int		map_check(int fd, char *path, t_game *mlx);
char	**get_map(int fd, char *path);
int		check_map_content(t_game *mlx);

//MAP_CHECK_UTILS.C

int		number_lines(int fd);
int		check_map_elements(t_game *mlx, char *line);
int		check_map_characters(char c);

//FREE.C
void	free_double_array(char **double_array);

//MOVEMENT.C
void	move_dot(int key_code, t_game *mlx);

#endif