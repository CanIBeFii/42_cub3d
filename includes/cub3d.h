/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:32:00 by fialexan          #+#    #+#             */
/*   Updated: 2023/08/11 15:22:25 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "./libft.h"

// SCREEN SIZE

# define SCREEN_W 640
# define SCREEN_H 480

//KEYS

# define ESC_KEY 65307

// TYPEDEF

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
}	t_player;

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_vector	img_size;
}	t_data;

typedef struct s_map_info
{
	t_data	no_texture;
	t_data	so_texture;
	t_data	ea_texture;
	t_data	we_texture;

	t_rgb	floor_color;
	t_rgb	ceiling_color;
}	t_map_info;

typedef struct s_map
{
	char		**map;
	int			x;
	int			y;
}	t_map;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*window;
	t_data		img;
	char		*path;

	t_map		map;
	t_map_info	info;

}	t_game;

// MAIN.C

void	cub3d(t_game *mlx);

// FILE_CHECKER.C

void	check_file(int argc, char **argv, t_game *mlx);

// MAP_CHECKER.C

void	map_checker(char *path, t_game *mlx);
int		get_map(int fd, t_map *map);
int		get_map_info(int fd, t_game *mlx);

// MAP_UTILS.C

char	**realloc_double_char_array(char **array, int new_line_size);
int		check_map_line(char *line);
int		is_valid_map_char(char c);
int		double_array_size(char **array);
char	*go_to_first_map_line(int fd);

// MAP_VALIDATOR.C

int		validate_map(t_map *map);
int		check_surroundings(t_map *map, int x, int y);
int		is_inside_map_char(char c);

// MAP_INFO.C

void	get_texture(t_game *mlx, t_data *texture, char *line);
int		check_dup_textures(t_game *mlx, char *line);
void	get_rgb_values(t_rgb *surface, t_rgb color);
int		check_missing_info(t_map_info *info);

// MAP_INFO_UTILS.C

int		check_info(char *line, t_game *mlx);
int		check_rgb_values(char *line, t_map_info *info);
int		check_texture_path(char *line, t_game *mlx);

// COLORS.COLORS

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

// FREE.C

void	free_double_array(char **array);

// HANDLE_WINDOW.C

void	create_window(t_game *mlx);
int		close_window(t_game *mlx);

// KEYS.C

int		keys(int key_code, t_game *mlx);

//DRAW_RAYS.C

void	draw_rays(t_game *mlx);

#endif