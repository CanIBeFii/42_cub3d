/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:02:55 by canibefii         #+#    #+#             */
/*   Updated: 2023/06/12 16:59:23 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_vector_f	get_angle_vector(float angle)
{
	t_vector_f	vector;

	vector.x = cos(angle);
	vector.y = sin(angle);
	return (vector);
}

t_vector_f	get_ray_distance(t_vector_f angle, t_vector_f player_pos
	, t_vector_i map_pos, t_vector_f step_unit_size)
{
	t_vector_f	ray_distance;

	if (angle.x < 0)
		ray_distance.x = (player_pos.x - map_pos.x) * step_unit_size.x;
	else
		ray_distance.x = ((map_pos.x + 1) - player_pos.x) * step_unit_size.x;
	if (angle.y < 0)
		ray_distance.y = (player_pos.y - map_pos.y) * step_unit_size.y;
	else
		ray_distance.y = ((map_pos.y + 1) - player_pos.y) * step_unit_size.y;
	return (ray_distance);
}

t_dda	init_dda_info(t_vector_f player_pos, t_vector_i map_pos,
	t_vector_f angle)
{
	t_dda	dda;

	dda.step_unit_size.x = abs(1 / angle.x);
	dda.step_unit_size.y = abs(1 / angle.y);
	dda.line_step.x = -1;
	dda.line_step.y = -1;
	if (angle.x < 0)
		dda.ray_distance.x = (player_pos.x - map_pos.x) * dda.step_unit_size.x;
	else
	{
		dda.line_step.x = 1;
		dda.ray_distance.x = ((map_pos.x + 1) - player_pos.x)
			* dda.step_unit_size.x;
	}
	if (angle.y < 0)
		dda.ray_distance.y = (player_pos.y - map_pos.y) * dda.step_unit_size.y;
	else
	{
		dda.line_step.y = 1;
		dda.ray_distance.y = ((map_pos.y + 1) - player_pos.y)
			* dda.step_unit_size.y;
	}
	return (dda);
}

t_vector_f	calculate_distance(t_vector_f player_pos, t_vector_f angle)
{
	t_vector_i	map_pos;
	t_dda		dda;

	map_pos.x = (int)player_pos.x;
	map_pos.y = (int)player_pos.y;
	dda = init_dda_info(player_pos, map_pos, angle);
}

void	dda(void)
{
	vector2D_float playerPos; // player position
	vetor2D_float angle; // angle of the ray casted
	vecto2D_int mapPos; // position of the map being checked
	
	vector2D_float rayStepSize; //
	rayStepSize.x = sqrt(1 + (angle.y / angle.x)) * (angle.y / angle.x);
	rayStepSize.y = sqrt(1 + (angle.x / angle.y)) * (angle.x / angle.y);
		
	vetor2D_int lineStep; // positive or negatie step of the angle
	vector2D_float raydistance;	// how many X and Y to move to get to the next wall
	
	if (angle.x < 0)
	{
		lineStep.x = -1;
		rayDistance.x = (playerPos.x - float(mapPos.x)) * rayStepSize.x;
	}
	else 
	{
		lineStep.x = 1;
		rayDistance.x = (float(mapPos.x + 1) - playerPos.x) * rayStepSize.x;
	}
	if (angle.y < 0)
	{
		lineStep.y = -1;
		rayDistance.y = (playerPos.y - float(mapPos.y)) * rayStepSize.y;
	}
	else 
	{
		lineStep.y = 1;
		rayDistance.y = (float(mapPos.y + 1) - playerPos.y) * rayStepSize.y;
	}
	float maxDistance;
	float distance;
	int hitWall;
	
	hitWall = 0;
	maxStep = 100;
	step = 0;
	
	while (hitWall == 0 && step < maxStep)
	{
		if (rayDistance.x < rayDistance.y)
		{
			mapPos.x += lineStep.x;
			distance = rayDistance.x;
			rayDistance.x += rayStepSize.x;
		}
		else
		{
			mapPos.y += lineStep.y;
			distance = rayDistance.y;
			rayDistance.y += rayStepSize.y;
		}
		
		if (mapPos.x < mapSize.x && mapPos.y < mapSize.y && mapPos.x >= 0 && mapPos.y >= 0)
		{
			if (map[mapPos.x][mapPos.y] == 1)
				hitWall = 1;
		}
	}
	
	vector2D_float distanceToWall;
	if (hitWall == 1)
	{
		distanceToWall.x = playerPos.x + angle.x * distance;
		distanceToWall.y = playerPos.y + angle.y * distance;
	}
	return distanceToWall;
}
