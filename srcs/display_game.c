/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:19:21 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/22 14:15:32 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

static bool	player_in_the_door(t_data *data)
{
	return (fabs(data->player.position.x - (double)data->door_coordinates.x) <= 1.5
	&& fabs(data->player.position.y - (double)data->door_coordinates.y) <= 1.5);
}

void	close_door(t_data *data)
{
	long	check_time;

	check_time = ft_get_current_time();
	if (data->map[data->door_coordinates.y][data->door_coordinates.x] == EMPTY
		&& !player_in_the_door(data)
		&& check_time - data->door_last_open >= 5000)
	{
		data->map[data->door_coordinates.y][data->door_coordinates.x] = DOOR;
		data->door_last_open = 0;
	}
}

int	display(t_data *data)
{
	dda(data);
	draw_map_fill(data);
	draw_flashlight(data);
	draw_player(data);
	update_sprite(data);
	draw_sprite(data);
	close_door(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
	return (1);
}
