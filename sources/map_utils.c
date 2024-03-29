/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:07:47 by fialexan          #+#    #+#             */
/*   Updated: 2023/09/06 17:44:26 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**realloc_double_char_array(char **array, int new_line_size, int index)
{
	int		size;
	int		line_size;
	char	**new_array;

	size = double_array_size(array);
	new_array = malloc(sizeof(char *) * (size + 2));
	if (new_array == NULL)
		return (NULL);
	while (index != size)
	{
		line_size = ft_strlen(array[index]);
		new_array[index] = malloc(sizeof(char) * new_line_size);
		ft_strlcpy(new_array[index], array[index], line_size + 1);
		free(array[index]);
		index++;
	}
	new_array[index] = NULL;
	new_array[index + 1] = NULL;
	free(array);
	return (new_array);
}

int	check_map_line(char *line)
{
	int		index;
	char	c;

	index = 0;
	if (line == NULL || ft_strcmp(line, "\n") == 0)
	{
		if (line != NULL)
			free(line);
		return (0);
	}
	while (line[index] != '\0' && line[index] != '\n')
	{
		c = line[index];
		if (is_valid_map_char(c) == 0)
		{
			free(line);
			line = NULL;
			return (print_error("Error: invalid map line", 0));
		}
		index += 1;
	}
	return (1);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'W' || c == 'E');
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

char	*go_to_first_map_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL && ft_strcmp(line, "\n") == 0)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}
