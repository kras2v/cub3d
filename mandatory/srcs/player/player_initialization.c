/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_initialization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:46:22 by valeriia          #+#    #+#             */
/*   Updated: 2025/08/03 09:14:57 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

static void	assign_direction(t_data *data, int x, int y)
{
	if (data->map[y][x] == NORTH)
	{
		data->player.direction.x = 0;
		data->player.direction.y = -1;
	}
	else if (data->map[y][x] == EAST)
	{
		data->player.direction.x = 1;
		data->player.direction.y = 0;
	}
	else if (data->map[y][x] == SOUTH)
	{
		data->player.direction.x = 0;
		data->player.direction.y = 1;
	}
	else if (data->map[y][x] == WEST)
	{
		data->player.direction.x = -1;
		data->player.direction.y = 0;
	}
}

void	init_player(t_data *data)
{
	int		y;
	int		x;
	bool	is_position_set;

	y = 0;
	x = 0;
	is_position_set = false;
	while (y < data->map_height && is_position_set == false)
	{
		x = 0;
		while (x < data->map_width && is_position_set == false)
		{
			if (is_direction(data->map[y][x]))
			{
				is_position_set = true;
				assign_direction(data, x, y);
			}
			x++;
		}
		y++;
	}
	data->player.position.x = x - 0.5;
	data->player.position.y = y - 0.5;
	data->player.plane.x = -data->player.direction.y * FOV;
	data->player.plane.y = data->player.direction.x * FOV;
}
