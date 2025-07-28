/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_managment_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:29:51 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/28 11:54:16 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda_bonus.h"

bool	is_door(int coordinate)
{
	return (coordinate == DOOR);
}

static bool	cast_flashlight_ray(
	t_data *data,
	t_fvector dir,
	int map_width,
	int map_height
)
{
	t_fvector		pos;
	double			len;
	t_coordinates	m;

	pos = data->player.position;
	len = 0;
	while (len < 2.0)
	{
		m.x = (int)pos.x;
		m.y = (int)pos.y;
		if (m.y < map_height && m.x < map_width && data->map[m.y][m.x] != EMPTY)
			break ;
		pos.x += dir.x * 0.1;
		pos.y += dir.y * 0.1;
		len += 0.1;
		if (is_door(data->map[(int)pos.y][(int)pos.x]))
		{
			data->map[(int)pos.y][(int)pos.x] = EMPTY;
			data->door_coordinates.x = (int)pos.x;
			data->door_coordinates.y = (int)pos.y;
			data->door_last_open = time_now();
			return (true);
		}
	}
	return (false);
}

void	open_door(t_data *data)
{
	t_flash_params	param;
	t_fvector		dir;
	int				i;
	double			a;

	param.map_start_x = get_minimum_tile(data->player.position.x);
	param.map_start_y = get_minimum_tile(data->player.position.y);
	param.player_pos.x = (data->player.position.x
			- param.map_start_x) * MINI_TILE;
	param.player_pos.y = (data->player.position.y
			- param.map_start_y) * MINI_TILE;
	param.fov = 1;
	param.rays = 120;
	param.step_angle = param.fov / (param.rays - 1);
	param.start = -param.fov / 2;
	i = 0;
	while (i++ < param.rays)
	{
		a = param.start + i * param.step_angle;
		rotate(&dir, data->player.direction, a);
		if (cast_flashlight_ray(data, dir,
				data->map_width, data->map_height))
			return ;
	}
}
