/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:28:59 by kvalerii          #+#    #+#             */
/*   Updated: 2025/08/01 18:24:20 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_bonus.h"

int	key_press_event(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		close_event(data);
	}
	if (keycode == XK_W || keycode == XK_w
		|| keycode == XK_S || keycode == XK_s
		|| keycode == XK_D || keycode == XK_d
		|| keycode == XK_A || keycode == XK_a
		|| keycode == XK_Right || keycode == XK_Left)
	{
		move_player(keycode, data);
	}
	else if (keycode == XK_space)
	{
		open_door(data);
	}
	return (0);
}

void	free_texture_name(t_data *data)
{
	int	i;

	i = 0;
	if (data->texture_names)
	{
		while (i < 4)
		{
			if (data->texture_names[i])
				free(data->texture_names[i]);
			data->texture_names[i] = NULL;
			i++;
		}
		free(data->texture_names);
	}
}

int	close_event(t_data *data)
{
	if (data)
	{
		free_texture_name(data);
		if (data->sprite)
		{
			free_sprite(data);
		}
		if (data->mlx)
		{
			free_mlx_data(data->mlx, data->img.ptr, data->mlx_win);
			mlx_destroy_display(data->mlx);
			free_textures(data);
			free(data->mlx);
		}
		if (data->script)
		{
			free_double_arr(data->script);
			if (data->script)
			{
							free(data->script);
			data->script = NULL;
			}
		}
	}
	exit(0);
	return (0);
}

int	mouse_move_callback(int x, int y, t_data *data)
{
	int		center_x;
	int		delta_x;
	double	rot_speed;

	(void)y;
	center_x = WIDTH / 2;
	delta_x = x - center_x;
	if (delta_x == 0)
		return (0);
	rot_speed = delta_x * 0.0002;
	if (delta_x != 0)
	{
		rotate(&data->player.direction, data->player.direction, rot_speed);
		rotate(&data->player.plane, data->player.plane, rot_speed);
		mlx_mouse_move(data->mlx, data->mlx_win, WIDTH / 2, HEIGHT / 2);
	}
	return (0);
}

//!STILL REACHABLE
void	init_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, ON_KEYDOWN, KEY_PRESS_MASK, key_press_event, data);
	mlx_hook(data->mlx_win, ON_DESTROY, NO_EVENT_MASK, close_event, data);
	mlx_hook(data->mlx_win, 6, 1L << 6, mouse_move_callback, data);
	mlx_mouse_hide(data->mlx, data->mlx_win);
}
