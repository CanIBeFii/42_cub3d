/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:12:41 by mibernar          #+#    #+#             */
/*   Updated: 2023/08/23 17:23:52 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_imgs(t_game *mlx, t_map_info *info)
{
	info->no_texture.img = mlx_xpm_file_to_image(mlx->mlx_ptr, info->no,
			&info->no_texture.img_size.x, &info->no_texture.img_size.y);
	info->so_texture.img = mlx_xpm_file_to_image(mlx->mlx_ptr, info->so,
			&info->so_texture.img_size.x, &info->so_texture.img_size.y);
	info->ea_texture.img = mlx_xpm_file_to_image(mlx->mlx_ptr, info->no,
			&info->ea_texture.img_size.x, &info->ea_texture.img_size.y);
	info->we_texture.img = mlx_xpm_file_to_image(mlx->mlx_ptr, info->no,
			&info->we_texture.img_size.x, &info->we_texture.img_size.y);
}
