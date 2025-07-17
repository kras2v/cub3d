/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:43:36 by valeriia          #+#    #+#             */
/*   Updated: 2025/07/17 12:26:50 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	get_player_position_on_map(
	t_data *data,
	t_point *player_position_in_cell
)
{
	player_position_in_cell->x = (data->player.position.x);
	player_position_in_cell->y = (data->player.position.y);
}

void	get_player_cell(
	t_point player_position_in_cell,
	t_coordinates *player_cell
)
{
	player_cell->x = (int)player_position_in_cell.x;
	player_cell->y = (int)player_position_in_cell.y;
}

void	get_x_ray_coordinates(
	int x,
	t_data *data,
	t_fvector *ray
)
{
	ray->x = data->player.direction.x
		+ data->player.plane.x * data->normalized_x[x];
	ray->y = data->player.direction.y
		+ data->player.plane.y * data->normalized_x[x];
}
