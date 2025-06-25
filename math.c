/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:25:18 by kvalerii          #+#    #+#             */
/*   Updated: 2025/06/25 20:39:14 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	rotate(t_fvector *point, double radian)
{
	t_fvector	temp;

	temp.x = point->x;
	temp.y = point->y;
	point->x = (temp.x * cos(radian) - temp.y * sin(radian));
	point->y = (temp.x * sin(radian) + temp.y * cos(radian));
}

void	swap_points(t_fvector *a, t_fvector *b)
{
	t_fvector temp;

	temp.x = a->x;
	temp.y = a->y;
	a->x = b->x;
	a->y = b->y;

	b->x = temp.x;
	b->y = temp.y;
}
