/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flashlight_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:44:39 by valeriia          #+#    #+#             */
/*   Updated: 2025/07/29 12:26:31 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

static t_fvector	cast_flashlight_ray(t_data *data, t_fvector dir,
		int map_start_x, int map_start_y)
{
	t_fvector	pos;
	t_fvector	end;
	double		len;
	int			mx;
	int			my;

	pos = data->player.position;
	len = 0;
	while (len < 2.0)
	{
		mx = (int)pos.x;
		my = (int)pos.y;
		if (my < data->map_height && mx < data->map_width
			&& data->map[my][mx] == WALL)
			break ;
		pos.x += dir.x * 0.1;
		pos.y += dir.y * 0.1;
		len += 0.1;
	}
	end.x = (pos.x - map_start_x) * MINI_TILE;
	end.y = (pos.y - map_start_y) * MINI_TILE;
	return (end);
}

void	draw_flashlight(t_data *data)
{
	t_flash_params	param;
	t_fvector		dir;
	t_fvector		end;
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
		end = cast_flashlight_ray(data, dir, param.map_start_x,
				param.map_start_y);
		draw_line(data, param.player_pos, end, WHITE);
	}
}
