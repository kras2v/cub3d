/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:25:18 by kvalerii          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/22 16:26:51 by eklymova         ###   ########.fr       */
=======
/*   Updated: 2025/07/29 12:26:32 by kvalerii         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

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
