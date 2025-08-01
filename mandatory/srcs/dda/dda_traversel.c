/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_traversel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:48:27 by valeriia          #+#    #+#             */
/*   Updated: 2025/07/29 12:22:46 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

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
		if ((data->map[player_cell.y][player_cell.x] == WALL)
			&& !is_direction(data->map[player_cell.y][player_cell.x]))
			hit = true;
	}
	if (dda_parameters->side == VERTICAL)
		return (dda_parameters->initial_step.x - dda_parameters->fixed_step.x);
	return (dda_parameters->initial_step.y - dda_parameters->fixed_step.y);
}
