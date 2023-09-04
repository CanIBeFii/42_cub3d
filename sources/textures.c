/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:12:41 by mibernar          #+#    #+#             */
/*   Updated: 2023/09/04 15:20:25 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_imgs(t_game *mlx, t_map_info *info)
{
	info->no_texture.img = mlx_xpm_file_to_image(mlx->mlx_ptr, info->no,
			&info->no_texture.img_size.x, &info->no_texture.img_size.y);
	info->no_texture.addr = mlx_get_data_addr(info->no_texture.img,
			&info->no_texture.bits_per_pixel, &info->no_texture.line_length,
			&info->no_texture.endian);
	info->so_texture.img = mlx_xpm_file_to_image(mlx->mlx_ptr, info->so,
			&info->so_texture.img_size.x, &info->so_texture.img_size.y);
	info->so_texture.addr = mlx_get_data_addr(info->so_texture.img,
			&info->so_texture.bits_per_pixel, &info->so_texture.line_length,
			&info->so_texture.endian);
	info->ea_texture.img = mlx_xpm_file_to_image(mlx->mlx_ptr, info->ea,
			&info->ea_texture.img_size.x, &info->ea_texture.img_size.y);
	info->ea_texture.addr = mlx_get_data_addr(info->ea_texture.img,
			&info->ea_texture.bits_per_pixel, &info->ea_texture.line_length,
			&info->ea_texture.endian);
	info->we_texture.img = mlx_xpm_file_to_image(mlx->mlx_ptr, info->we,
			&info->we_texture.img_size.x, &info->we_texture.img_size.y);
	info->we_texture.addr = mlx_get_data_addr(info->we_texture.img,
			&info->we_texture.bits_per_pixel, &info->we_texture.line_length,
			&info->we_texture.endian);
}
