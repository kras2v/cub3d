/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:24:19 by kvalerii          #+#    #+#             */
/*   Updated: 2025/06/26 15:01:35 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

bool	is_wall(t_data *data, double shift_x, double shift_y)
{
	double	player_size_in_cell;

	player_size_in_cell = ((double)PLAYER_SIZE / 2.0) / (double)CELL_SIZE;
	if (data->map[(int)(data->player.position.y - player_size_in_cell + shift_y)][(int)(data->player.position.x - player_size_in_cell + shift_x)] == WALL
		|| data->map[(int)(data->player.position.y - player_size_in_cell + shift_y)][(int)(data->player.position.x + player_size_in_cell + shift_x)] == WALL
		|| data->map[(int)(data->player.position.y + player_size_in_cell +  shift_y)][(int)(data->player.position.x + player_size_in_cell +  shift_x)] == WALL
		|| data->map[(int)(data->player.position.y + player_size_in_cell +  shift_y)][(int)(data->player.position.x - player_size_in_cell +  shift_x)] == WALL)
	{
		return (true);
	}
	return (false);
}

void	slide(t_data *data, double shift_x, double shift_y, double move_speed)
{
	if (is_wall(data, shift_x * move_speed, 0) == false)
		data->player.position.x += shift_x * move_speed;
	if (is_wall(data, 0, shift_y * move_speed) == false)
		data->player.position.y += shift_y * move_speed;
}

int	move_player(int keycode, t_data *data)
{
	double					move_speed;
	double					rot_speed;
	double					shift_x;
	double					shift_y;

	if (keycode == XK_W || keycode == XK_w
		|| keycode == XK_S || keycode == XK_s
		|| keycode == XK_A || keycode == XK_a
		|| keycode == XK_D || keycode == XK_d
		|| keycode == XK_Left || keycode == XK_Right)
	{
		display(data);
		move_speed = 0.3;
		rot_speed = 0.05;
		shift_x = 0;
		shift_y = 0;
		if (keycode == XK_W || keycode == XK_w)
		{
			shift_x += data->player.direction.x * move_speed;
			shift_y += data->player.direction.y * move_speed;
		}
		if (keycode == XK_S || keycode == XK_s)
		{
			shift_x -= data->player.direction.x * move_speed;
			shift_y -= data->player.direction.y * move_speed;
		}
		if (keycode == XK_A || keycode == XK_a)
		{
			shift_x += data->player.direction.y * move_speed;
			shift_y -= data->player.direction.x * move_speed;
		}
		if (keycode == XK_D || keycode == XK_d)
		{
			shift_x -= data->player.direction.y * move_speed;
			shift_y += data->player.direction.x * move_speed;
		}
		slide(data, shift_x, shift_y, move_speed);
		if (keycode == XK_Left)
		{
			rotate(&(data->player.direction), -rot_speed);
			rotate(&(data->player.plane), -rot_speed);
		}
		else if (keycode == XK_Right)
		{
			rotate(&(data->player.direction), rot_speed);
			rotate(&(data->player.plane), rot_speed);
		}
	}
	return (0);
}
