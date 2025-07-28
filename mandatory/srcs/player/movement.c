/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:24:19 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/23 16:02:01 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

static void	slide(
	t_player *player,
	char **map,
	t_point shift
)
{
	t_point	shift_with_move;

	shift_with_move = shift;
	shift_with_move.x *= MOVE_SPEED;
	shift_with_move.y = 0;
	if (!is_colliding(*player, map, shift_with_move, &is_wall))
		player->position.x += shift.x * MOVE_SPEED;
	shift_with_move = shift;
	shift_with_move.x = 0;
	shift_with_move.y *= MOVE_SPEED;
	if (!is_colliding(*player, map, shift_with_move, &is_wall))
		player->position.y += shift.y * MOVE_SPEED;
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
	slide(&data->player, data->map, shift);
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
