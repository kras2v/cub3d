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

void	free_sprite(t_data *data)
{
	int	i;

	if (!data || !data->sprite)
		return;
	i = 0;
	if (data->sprite->texture)
	{
		while (i < 2)
		{
			if (data->sprite->texture[i])
			{
				if (data->sprite->texture[i]->image.ptr)
					mlx_destroy_image(data->mlx, data->sprite->texture[i]->image.ptr);
				free(data->sprite->texture[i]);
			}
			i++;
		}
		free(data->sprite->texture);
	}
	free(data->sprite);
}
