/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:32:00 by fialexan          #+#    #+#             */
/*   Updated: 2023/07/27 17:01:54 by mibernar         ###   ########.fr       */
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

//SCREEN SIZE

# define SCREEN_W 640
# define SCREEN_H 480

//KEYS

# define ESC_KEY 65307

// TYPEDEF

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_map_info
{
	int		north_texture;
	int		south_texture;
	int		east_texture;
	int		west_texture;
	t_rgb	floor_color;
	t_rgb	ceiling_color;
}	t_map_info;

typedef struct s_map
{
	t_map_info	*info;
	char		**map;
	int			x;
	int			y;
}	t_map;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*window;
	t_data	img;
	char	*path;
}	t_game;

//MAIN.C

void	cub3d(t_game *mlx);

// FILE_CHECKER.C

int		check_file(int argc, char **argv, t_game *mlx);

// MAP_CHECKER.C

void	map_checker(char *path);
t_map	*get_map(int fd, t_map_info *info);
void	get_map_info(int fd);
int		check_info(char *line);
int		check_rgb_values(char *line);
int		check_texture_path(char *line);

// MAP_UTILS.C

char	**realloc_double_char_array(char **array);
int		double_array_size(char **array);

//COLORS.COLORS

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

// FREE.C

void	free_double_array(char **array);
void	free_map(t_map *map);

//HANDLE_WINDOW.C

void	create_window(t_game *mlx);
int		close_window(t_game *mlx);

//KEYS.C

int		keys(int key_code, t_game *mlx);

#endif