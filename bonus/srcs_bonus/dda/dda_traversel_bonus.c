/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_traversel_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:48:27 by valeriia          #+#    #+#             */
/*   Updated: 2025/07/29 15:28:00 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_bonus.h"

void	make_step_to_next_cell(
	t_dda_parameters *dda_parameters,
	t_coordinates *player_cell
)
{
	if (dda_parameters->initial_step.x < dda_parameters->initial_step.y)
	{
		dda_parameters->initial_step.x += dda_parameters->fixed_step.x;
		player_cell->x += dda_parameters->step.x;
		dda_parameters->side = VERTICAL;
	}
	else
	{
		dda_parameters->initial_step.y += dda_parameters->fixed_step.y;
		player_cell->y += dda_parameters->step.y;
		dda_parameters->side = HORIZONTAL;
	}
}

bool	check_hit_with_object(
	t_data *data,
	t_coordinates player_cell
)
{
	return ((is_wall(data->map[player_cell.y][player_cell.x])
		|| is_door(data->map[player_cell.y][player_cell.x]))
		&& !is_direction(data->map[player_cell.y][player_cell.x]));
}

double	find_distance_to_wall(
	t_data *data,
	t_dda_parameters *dda_parameters,
	t_coordinates player_cell
)
{
	int	hit;

	hit = false;
	dda_parameters->side = VERTICAL;
	while (hit == false)
	{
		if (dda_parameters->initial_step.x < dda_parameters->initial_step.y)
		{
			dda_parameters->initial_step.x += dda_parameters->fixed_step.x;
			player_cell.x += dda_parameters->step.x;
			dda_parameters->side = VERTICAL;
		}
		else
		{
			dda_parameters->initial_step.y += dda_parameters->fixed_step.y;
			player_cell.y += dda_parameters->step.y;
			dda_parameters->side = HORIZONTAL;
		}
		hit = check_hit_with_object(data, player_cell);
		if (data->map[player_cell.y][player_cell.x] == DOOR)
			dda_parameters->door_in_fov = true;
	}
	if (dda_parameters->side == VERTICAL)
		return (dda_parameters->initial_step.x - dda_parameters->fixed_step.x);
	return (dda_parameters->initial_step.y - dda_parameters->fixed_step.y);
}
