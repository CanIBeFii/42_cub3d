/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:32:28 by mibernar          #+#    #+#             */
/*   Updated: 2023/05/25 16:54:16 by mibernar         ###   ########.fr       */
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

//SCREEN SIZW

# define SCREEN_H 1080
# define SCREEN_W 1920

//PI

# define PI 3.1415926535

//KEY_CODES

# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define L_ARROW 65361
# define R_ARROW 65363
# define ESC_KEY 65307

typedef struct s_bresenham
{
	int	absolute_x;
	int	absolute_y;
	int	x_modifier;
	int	y_modifier;
	int	abs_diff;
	int	abs_diff2x;	
}	t_bresenham;

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
	int	map_x;
	int	map_y;
}t_map;

typedef struct s_vector
{
	int	x;
	int	y;
}t_vector;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_data;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*window;
	void		*map_window;
	t_vector	window_size;
	t_map		map_info;
	t_player	player;
	t_data		img;
	t_data		map_img;
	char		**map;
	char		**map_layout;
}t_game;

//MAIN.C
void		cub3d(int fd, char *path);
void		game_init(t_game mlx);

//WINDOW_MANAGEMENT.C
int			close_window(t_game *mlx);

//HANDLE_KEYS.C
int			keys(int keycode, t_game *mlx);

//MAP_CHECK.C
void		player_orientation(t_game *mlx, int i, int x);
int			map_check(int fd, char *path, t_game *mlx);
char		**get_map(int fd, char *path);
int			check_map_content(t_game *mlx);

//MAP_CHECK_UTILS.C
int			number_lines(int fd);
int			check_map_elements(t_game *mlx, char *line);
int			check_map_characters(t_game *mlx, int i, int x);

//FREE.C
void		free_double_array(char **double_array);

//MOVEMENT.C
void		move_dot(int key_code, t_game *mlx);
void		movement_keys(int key_code, t_game *mlx);
void		direction_keys(int key_code, t_game *mlx);

//DRAW.C
void		draw_square(t_game *mlx, int x, int y, int color);
void		draw_line(t_game *mlx, float x2, float y2, int color);
void		draw_map(t_game *mlx);
void		draw_player(t_game *mlx, int x, int y, int color);

//BRESENHAM.C
void		bresenham_algo(t_vector begin, t_vector end, t_game *mlx);
void		bresenham_loop(t_vector begin, t_vector end, t_game *mlx,
				t_bresenham algo);
t_bresenham	bresenham_init(t_vector begin, t_vector end);

//RAYS.C
void		draw_rays(t_game *mlx, float x2, float y2, float loop);
t_vector	get_end_ray_cordinates(t_game *mlx, float loop, float x0, float y0);

//MY_MLX_FUNCTIONS.C
void		my_img_clear(t_game *mlx, t_data data);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

//3D.C
void		draw_ceiling(t_game *mlx, float distance, int ray_id);
void		draw_floor(t_game *mlx, float distance, int ray_id);
void		draw_walls(t_game *mlx, float distance, int ray_id);
void		draw_3d(t_game *mlx, float distance, int ray_id, float ray_angle);

#endif