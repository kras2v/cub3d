/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_helpers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:55:52 by kvalerii          #+#    #+#             */
/*   Updated: 2025/08/04 16:18:46 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HELPERS_H
# define MATH_HELPERS_H

# include "math_helpers.h"

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

typedef struct s_fvector	t_point;

void	rotate(t_fvector *dir, t_fvector temp, double radian);
void	swap_points(t_fvector *a, t_fvector *b);

#endif