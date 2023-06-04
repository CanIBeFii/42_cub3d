/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canibefii <canibefii@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:02:55 by canibefii         #+#    #+#             */
/*   Updated: 2023/06/04 11:52:50 by canibefii        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

vector2D_int {
	int x;
	int y;
}

vector2D_float {
	float x;
	float y;
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
	
	if (hitWall == 1)
	{
		if (distance == rayDistance.x)
			distance = distance * cos(angle.x - playerPos.x) * 2;
		else
			distance = distance * cos(angle.y - playerPos.y) * 2;
	}
}