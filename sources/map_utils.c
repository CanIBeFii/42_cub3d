/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:07:47 by fialexan          #+#    #+#             */
/*   Updated: 2023/07/25 15:32:27 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**realloc_double_char_array(char **array)
{
	int		size;
	int		index;
	char	**new_array;

	index = 0;
	size = double_array_size(array);
	new_array = malloc(sizeof(char *) * (size + 2));
	if (new_array == NULL)
		return (NULL);
	while (index != size)
	{
		new_array[index] = ft_strdup(array[index]);
		free(array[index]);
		index++;
	}
	new_array[index] = NULL;
	new_array[index + 1] = NULL;
	free(array);
	return (new_array);
}

int	double_array_size(char **array)
{
	int	size;

	size = 0;
	if (array == NULL)
		return (0);
	while (array[size] != NULL)
		size++;
	return (size);
}
