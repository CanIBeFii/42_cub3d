/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:32:00 by fialexan          #+#    #+#             */
/*   Updated: 2023/08/30 16:40:48 by mibernar         ###   ########.fr       */
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
# define FOV 60

//KEYS

# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define L_ARROW 65361
# define R_ARROW 65363
# define ESC_KEY 65307

//VALUES

# define MOVE_SPEED 0.1
# define ROT_SPEED 0.5

// TYPEDEF

typedef struct s_vector_int
{
	int	x;
	int	y;
}	t_vector_int;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_vector_int	img_size;
}	t_data;

typedef struct s_map_info
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;

	t_data	no_texture;
	t_data	so_texture;
	t_data	ea_texture;
	t_data	we_texture;

	t_rgb	floor_color;
	t_rgb	ceiling_color;
}	t_map_info;

typedef struct s_vector
{
	double	y;
	double	x;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	direction;
	t_vector	camera;
}	t_player;

typedef struct s_ray
{
	t_vector		direction;
	t_vector_int	map_pos;
	t_vector		delta_dist;
	t_vector		distance;
	t_vector_int	step;

	double			real_distance;
	int				wall_start;
	int				wall_end;

	int				side;
	int				x_texture;
}	t_ray;

typedef struct s_map
{
	char		**map;
	int			max_x;
	int			max_y;

	t_player	player;
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
int		get_map(int fd, t_map *map, int index);
int		get_map_info(int fd, t_game *mlx);

// MAP_UTILS.C

char	**realloc_double_char_array(char **array, int new_line_size, int index);
int		check_map_line(char *line);
int		is_valid_map_char(char c);
int		double_array_size(char **array);
char	*go_to_first_map_line(int fd);

// MAP_VALIDATOR.C

int		validate_map(t_map *map);
int		check_surroundings(t_map *map, int x, int y);
int		is_out(t_map *map, int y, int x);
int		is_inside_map_char(char c);

// MAP_INFO.C

void	get_rgb_values(t_rgb *surface, t_rgb color);
int		check_missing_info(t_map_info *info);

// MAP_INFO_UTILS.C

int		check_dup_textures(t_game *mlx, char *line, char *path);
int		check_info(char *line, t_game *mlx);
int		check_rgb_values(char *line, t_map_info *info, int x);
int		check_values(char **rgb_char);
int		check_texture_path(char *line, t_game *mlx, int x);

// PLAYER.C

int		save_player_pos(t_player *player, int spawn_y,
			int spawn_x, char spawn_dir);

// DDA.C

void	dda(t_game *mlx, t_map *map, t_player *player, t_map_info *info);
void	dda_step_calc(t_ray *ray, t_player *player);
void	dda_real_distance_calc(t_ray *ray, t_map *map);
void	dda_wall_height(t_ray *ray);
void	dda_side_selector(t_game *mlx, t_ray *ray, t_player *player, t_map_info *info);

// COLORS.COLORS

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

// FREE.C

void	free_double_array(char **array);
void	free_game(t_game *mlx);

// ERROR.C

int		print_error(char *message, int return_value);

// HANDLE_WINDOW.C

void	create_window(t_game *mlx);
int		close_window(t_game *mlx);

// KEYS.C

int		keys(int key_code, t_game *mlx);

//TEXTURES.C

void	open_imgs(t_game *mlx, t_map_info *info);

//DRAW_RAYS.C

void	draw_rays(t_game *mlx);

//MOVEMENTS.C

void	movement_up_down(t_player *player, t_map *map, int key_code);
void	movement_left_right(t_player *player, t_map *map, int key_code);
void	camera_changes(int key_code, t_player *player);

//DRAW.C

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		get_color(int tex_x, int tex_y, t_data *curr);
void	draw_walls(t_game *mlx, t_ray *ray, t_data *texture, double wall_height);

#endif