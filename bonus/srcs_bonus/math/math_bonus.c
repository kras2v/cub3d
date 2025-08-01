/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:25:18 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/29 12:31:20 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_bonus.h"

void	rotate(t_fvector *dir, t_fvector temp, double radian)
{
	t_fvector	temp_v;

	temp_v.x = temp.x;
	temp_v.y = temp.y;
	dir->x = (temp_v.x * cos(radian) - temp_v.y * sin(radian));
	dir->y = (temp_v.x * sin(radian) + temp_v.y * cos(radian));
}

void	swap_points(t_fvector *a, t_fvector *b)
{
	t_fvector	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
