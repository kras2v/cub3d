/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_step.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:41:56 by valeriia          #+#    #+#             */
/*   Updated: 2025/07/16 20:08:35 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	get_direction_step(
	t_dda_parameters *dda_parameters
)
{
	dda_parameters->step.x = 1;
	if (dda_parameters->ray.x < 0)
	{
		dda_parameters->step.x = -1;
	}
	dda_parameters->step.y = 1;
	if (dda_parameters->ray.y < 0)
	{
		dda_parameters->step.y = -1;
	}
}

static double	calculate_initial_step(
	double ray,
	double player_position_in_cell,
	double fixed_step,
	int player_cell
)
{
	if (ray < 0)
	{
		return ((player_position_in_cell - (double)player_cell) * fixed_step);
	}
	else
	{
		return ((player_cell + 1.0 - player_position_in_cell) * fixed_step);
	}
}

void	get_initial_step(
	t_dda_parameters *params
)
{
	params->initial_step.x = calculate_initial_step(
			params->ray.x,
			params->player_position_in_cell.x,
			params->fixed_step.x,
			params->player_cell.x);
	params->initial_step.y = calculate_initial_step(
			params->ray.y,
			params->player_position_in_cell.y,
			params->fixed_step.y,
			params->player_cell.y);
}

void	get_fixed_step_between_lines(
	t_fvector ray,
	t_fvector *fixed_step
)
{
	fixed_step->x = INFINITY;
	if (ray.x != 0)
	{
		fixed_step->x = fabs(1.0 / ray.x);
	}
	fixed_step->y = INFINITY;
	if (ray.y != 0)
	{
		fixed_step->y = fabs(1.0 / ray.y);
	}
}
