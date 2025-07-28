/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_colision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:16:28 by valeriia          #+#    #+#             */
/*   Updated: 2025/07/22 13:55:22 by kvalerii         ###   ########.fr       */
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

int	shifted_tile(char **map, t_point old, t_point shift)
{
	return (map[(int)(old.y + shift.y)][(int)(old.x + shift.x)]);
}

bool	is_colliding(
	t_player player,
	char **map,
	t_point shift,
	bool (*checker)(int)
)
{
	assign_player_sides(&player);
	return (checker(shifted_tile(map, player.left_side.up, shift))
		|| checker(shifted_tile(map, player.left_side.down, shift))
		|| checker(shifted_tile(map, player.right_side.down, shift))
		|| checker(shifted_tile(map, player.right_side.up, shift)));
}
