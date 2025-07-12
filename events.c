/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:28:59 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/11 16:49:27 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

int	key_press_event(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		close_event(data);
	}
	if ((keycode == XK_W || keycode == XK_w)
		|| (keycode == XK_S || keycode == XK_s)
		|| (keycode == XK_D || keycode == XK_d)
		|| (keycode == XK_A || keycode == XK_a )
		|| (keycode == XK_Right || keycode == XK_Left))
	{
		move_player(keycode, data);
		display(data);
	}
	return (0);
}

int print_coords(int button, int x, int y, t_data *param)
{
	(void)param;
	(void)button;
	printf("px: %d | py: %d | map_x: %d | map_y: %d | is_wall: %d|\n", x - WIDTH, y, ( x - WIDTH) / CELL_SIZE, y / CELL_SIZE, param->map[y / CELL_SIZE][(x - WIDTH) / CELL_SIZE] > 0
		&& !is_direction(param->map[y / CELL_SIZE][(x - WIDTH) / CELL_SIZE]));
	return (0);
}

//TODO 
int	close_event(t_data *data)
{
	int i = 0;

	if (data && data->mlx)
	{
		if (data->img.ptr)
			mlx_destroy_image(data->mlx, data->img.ptr);
		if (data->mlx_win)
			mlx_destroy_window(data->mlx, data->mlx_win);
		if (data->texture)
		{
			while (i < 4)
			{
				if (data->texture[i].image.ptr)
					mlx_destroy_image(data->mlx, data->texture[i].image.ptr);
				i++;
			}
			free(data->texture);
		}
		if (data->N_T)
			free(data->N_T);
		if (data->S_T)
			free(data->S_T);
		if (data->E_T)
			free(data->E_T);
		if (data->W_T)
			free(data->W_T);
		if (data->F)
			free(data->F);
		if (data->C)
			free(data->C);
		mlx_destroy_display(data->mlx);
		free_double_arr(data->script);
		data->script = NULL;
		free(data->mlx);
		free_double_arr(data->lekkereclrs);
		free(data);
	}
	exit(0);
	return(0);
}

// int mouse_move_callback(int x, int y, t_data *data)
// {
// 	(void)y;
// 	static int last_x = WIDTH / 2;
// 	int delta_x = x - last_x;
// 	last_x = x;
// 	double rot_speed = delta_x * 0.002; // Коэффициент для плавности, можешь уменьшить/увеличить
// 	if (delta_x != 0)
// 	{
// 		double old_dir_x = data->player.direction.x;
// 		data->player.direction.x = data->player.direction.x * cos(rot_speed) - data->player.direction.y * sin(rot_speed);
// 		data->player.direction.y = old_dir_x * sin(rot_speed) + data->player.direction.y * cos(rot_speed);
// 		double old_plane_x = data->player.plane.x;
// 		data->player.plane.x = data->player.plane.x * cos(rot_speed) - data->player.plane.y * sin(rot_speed);
// 		data->player.plane.y = old_plane_x * sin(rot_speed) + data->player.plane.y * cos(rot_speed);
// 		display(data);
// 	}
// 	return 0;
// }

// int mouse_move_callback(int x, int y, t_data *data)
// {
// 	(void)y;
//     int center_x = WIDTH / 2;
//     int delta_x = x - center_x;
//     if (delta_x == 0)
//         return 0;
//     double rot_speed = delta_x * 0.0002;
//     if (delta_x != 0)
//     {
// 		double old_dir_x = data->player.direction.x;
// 		data->player.direction.x = data->player.direction.x * cos(rot_speed) - data->player.direction.y * sin(rot_speed);
// 		data->player.direction.y = old_dir_x * sin(rot_speed) + data->player.direction.y * cos(rot_speed);
// 		double old_plane_x = data->player.plane.x;
// 		data->player.plane.x = data->player.plane.x * cos(rot_speed) - data->player.plane.y * sin(rot_speed);
// 		data->player.plane.y = old_plane_x * sin(rot_speed) + data->player.plane.y * cos(rot_speed);
//         mlx_mouse_move(data->mlx, data->mlx_win, WIDTH / 2, HEIGHT / 2);
// 		display(data);
//     }
//     return 0;
// }

void	init_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, ON_DESTROY, NO_EVENT_MASK, close_event, data);
	mlx_mouse_hook(data->mlx_win, print_coords, data);
	mlx_hook(data->mlx_win, ON_KEYDOWN, KEY_PRESS_MASK, key_press_event, data);
	mlx_hook(data->mlx_win, 6, 1L << 6, mouse_move_callback, data);
}
