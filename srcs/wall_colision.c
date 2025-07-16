/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_colision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:16:28 by valeriia          #+#    #+#             */
/*   Updated: 2025/07/16 22:17:55 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	assign_player_sides(t_player *player)
{
	double	size_in_cell;

	size_in_cell = ((double)PLAYER_SIZE / 2.0) / (double)MINI_TILE;
	player->left_side.up.x = player->position.x - size_in_cell;
	player->left_side.up.y = player->position.y - size_in_cell;
	player->left_side.down.x = player->position.x - size_in_cell;
	player->left_side.down.y = player->position.y + size_in_cell;
	player->right_side.up.x = player->position.x + size_in_cell;
	player->right_side.up.y = player->position.y - size_in_cell;
	player->right_side.down.x = player->position.x + size_in_cell;
	player->right_side.down.y = player->position.y + size_in_cell;
}

bool	is_wall(int coordinate)
{
	return (coordinate == WALL);
}

int	shifted_tile(char **map, t_point old, double shift_y, double shift_x)
{
	return (map[(int)(old.y + shift_y)][(int)(old.x + shift_x)]);
}

bool	is_colliding_with_wall(
	t_player player,
	char **map,
	double shift_x,
	double shift_y
)
{
	assign_player_sides(&player);
	return (is_wall(shifted_tile(map, player.left_side.up, shift_y, shift_x))
		|| is_wall(shifted_tile(map, player.left_side.down, shift_y, shift_x))
		|| is_wall(shifted_tile(map, player.right_side.down, shift_y, shift_x))
		|| is_wall(shifted_tile(map, player.right_side.up, shift_y, shift_x)));
}
