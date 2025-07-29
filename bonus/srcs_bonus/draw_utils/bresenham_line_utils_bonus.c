/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:52:37 by valeriia          #+#    #+#             */
/*   Updated: 2025/07/29 12:31:19 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_bonus.h"

void	get_direction(int *dir, int *delta)
{
	if ((*delta) < 0)
	{
		*dir = -1;
	}
	else
	{
		*dir = 1;
	}
	(*delta) *= (*dir);
}

void	assign_delta_coords(t_coordinates *delta, t_fvector *a, t_fvector *b)
{
	if (a->y > b->y)
	{
		swap_points(a, b);
	}
	delta->x = b->x - a->x;
	delta->y = b->y - a->y;
}

void	increase_stepping(
	int *p,
	int dir,
	t_coordinates *coords,
	t_coordinates delta
)
{
	if ((*p) >= 0)
	{
		coords->x += dir;
		(*p) = (*p) - 2 * delta.y;
	}
}

void	swap_axis(t_fvector *a)
{
	t_fvector	temp;

	temp = *a;
	a->x = temp.y;
	a->y = temp.x;
}
