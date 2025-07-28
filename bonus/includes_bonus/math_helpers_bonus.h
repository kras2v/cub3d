/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_helpers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:55:52 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/28 12:18:27 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HELPERS_BONUS_H
# define MATH_HELPERS_BONUS_H

#include "math_helpers.h"

typedef struct s_fvector
{
	double	x;
	double	y;
}	t_fvector;

typedef struct s_coordinates
{
	int	x;
	int	y;
}	t_coordinates;

typedef struct s_fvector t_point;

void	rotate(t_fvector *dir, t_fvector temp, double radian);
void	swap_points(t_fvector *a, t_fvector *b);

#endif