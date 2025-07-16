/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:24:19 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/16 22:17:55 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	slide(
	t_player *player,
	char **map,
	double shift_x,
	double shift_y
)
{
	if (is_colliding_with_wall(*player, map, shift_x * MOVE_SPEED, 0) == false)
		player->position.x += shift_x * MOVE_SPEED;
	if (is_colliding_with_wall(*player, map, 0, shift_y * MOVE_SPEED) == false)
		player->position.y += shift_y * MOVE_SPEED;
}

void	change_player_position(
	t_point *shift,
	int keycode,
	t_player *player
)
{
	if (keycode == XK_W || keycode == XK_w)
	{
		shift->x += player->direction.x * MOVE_SPEED;
		shift->y += player->direction.y * MOVE_SPEED;
	}
	if (keycode == XK_S || keycode == XK_s)
	{
		shift->x -= player->direction.x * MOVE_SPEED;
		shift->y -= player->direction.y * MOVE_SPEED;
	}
	if (keycode == XK_A || keycode == XK_a)
	{
		shift->x += player->direction.y * MOVE_SPEED;
		shift->y -= player->direction.x * MOVE_SPEED;
	}
	if (keycode == XK_D || keycode == XK_d)
	{
		shift->x -= player->direction.y * MOVE_SPEED;
		shift->y += player->direction.x * MOVE_SPEED;
	}
}

int	move_player(int keycode, t_data *data)
{
	t_point	shift;

	shift.x = 0;
	shift.y = 0;
	change_player_position(&shift, keycode, &data->player);
	slide(&data->player, data->map, shift.x, shift.y);
	if (keycode == XK_Left)
	{
		rotate(&(data->player.direction), data->player.direction, -ROT_SPEED);
		rotate(&(data->player.plane), data->player.plane, -ROT_SPEED);
	}
	else if (keycode == XK_Right)
	{
		rotate(&(data->player.direction), data->player.direction, ROT_SPEED);
		rotate(&(data->player.plane), data->player.plane, ROT_SPEED);
	}
	return (0);
}
