/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:42:57 by fialexan          #+#    #+#             */
/*   Updated: 2023/05/31 18:46:21 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	str_to_color(char *str)
{
	int		r;
	int		g;
	int		b;
	char	**rgb;

	rgb = ft_split(str, ',');
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
	return (get_color(r, g, b));
}

int	get_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
