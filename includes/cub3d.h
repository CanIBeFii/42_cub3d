/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:32:28 by mibernar          #+#    #+#             */
/*   Updated: 2023/06/01 15:33:21 by fialexan         ###   ########.fr       */
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
# include "../libft/includes/libft.h"

# define PI 3.1415926535

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
}	t_player;

typedef struct s_map_info
{
	char	*north_texture;
	char	*east_texture;
	char	*south_texture;
	char	*west_texture;
	int		ground_color;
	int		sky_color;
}	t_map_info;

typedef struct s_map
{
	t_map_info	*info;
	char		**map;
	int			map_x;
	int			map_y;
}	t_map;

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_rays
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
}	t_rays;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*window;
	t_vector	window_size;
	t_map		map_info;
	t_player	player;
	t_data		img;
	t_rays		rays;
	char		**map;
	char		**map_layout;
}	t_game;

//MAIN.C
void		cub3d(int fd, char *path);
void		game_init(t_game mlx);

// PARSER.C

t_map		*parser(char *path);

t_map_info	*get_map_info(int fd);

int			assign_path_to_info(t_map_info *info, char *line);

int			is_possible_line(char *line);

int			has_all_info(t_map_info *info);

// PARSER_UTILS.C

int			is_valid_file(char *path);

int			check_file_type(char *path);

t_map_info	*init_info(void);

// COLOR.C

int			str_to_color(char *str);

int			get_color(int r, int g, int b);

//WINDOW_MANAGEMENT.C
int			close_window(t_game *mlx);

//HANDLE_KEYS.C
int			keys(int keycode, t_game *mlx);

//MAP_CHECK.C
int			map_check(int fd, char *path, t_game *mlx);
char		**get_map(int fd, char *path);
int			check_map_content(t_game *mlx);

//MAP_CHECK_UTILS.C

int			number_lines(int fd);
int			check_map_elements(t_game *mlx, char *line);
int			check_map_characters(char c);

//FREE.C

void		free_double_array(char **double_array);

void		free_map_info(t_map_info *info);

//MOVEMENT.C
void		move_dot(int key_code, t_game *mlx);

//DRAW.C
void		draw_rays(t_game *mlx, float x2, float y2, int color);
void		my_img_clear(t_game *mlx);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		draw_square(t_game *mlx, int x, int y, int color);
void		draw_line(t_game *mlx, float x2, float y2, int color);
void		draw_map(t_game *mlx);
void		draw_player(t_game *mlx, int x, int y, int color);

//BRESENHAM.C
void		bresenham_algo(t_vector begin, t_vector end, t_game *mlx);
void		bresenham_loop(t_vector begin, t_vector end, t_game *mlx, t_bresenham algo);
t_bresenham	bresenham_init(t_vector begin, t_vector end);

#endif