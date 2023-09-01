/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:05:38 by fialexan          #+#    #+#             */
/*   Updated: 2023/09/01 18:10:30 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_double_array(char **array)
{
	int	index;

	index = 0;
	if (array == NULL)
		return ;
	while (array[index] != NULL)
	{
		free(array[index]);
		index++;
	}
	free(array);
	array = NULL;
}

void	free_mlx(t_game *mlx)
{
	if (mlx->info.no_texture.img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->info.no_texture.img);
	if (mlx->info.so_texture.img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->info.so_texture.img);
	if (mlx->info.ea_texture.img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->info.ea_texture.img);
	if (mlx->info.we_texture.img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->info.we_texture.img);
	if (mlx->img.img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->window);
	mlx_destroy_display(mlx->mlx_ptr);
	free (mlx->mlx_ptr);
}

void	free_game(t_game *mlx)
{
	if (mlx->map.map != NULL)
		free_double_array(mlx->map.map);
	if (mlx->info.no)
		free(mlx->info.no);
	if (mlx->info.so)
		free(mlx->info.so);
	if (mlx->info.ea)
		free(mlx->info.ea);
	if (mlx->info.we)
		free(mlx->info.we);
	if (mlx->game_started == 1)
		free_mlx(mlx);
}
