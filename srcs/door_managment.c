/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_managment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:29:51 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/18 18:59:42 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

bool	is_door(int coordinate)
{
	return (coordinate == DOOR);
}

int open_door(t_data *data)
{
	t_point	shift;

	shift.x = data->player.direction.x * MOVE_SPEED;
	shift.y = data->player.direction.y * MOVE_SPEED;
	printf("doooor = %c  []\n ", data->map[(int)(data->player.position.x + shift.y)][(int)(data->player.position.x + shift.x)]);
	if (is_colliding(data->player, data->map, shift, &is_door))
	{
		data->map[(int)(data->player.position.x + shift.y)][(int)(data->player.position.x + shift.x)] = EMPTY;
	}
	return (0);
}
