/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_helpers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:55:52 by kvalerii          #+#    #+#             */
/*   Updated: 2025/08/03 09:18:05 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HELPERS_BONUS_H
# define MATH_HELPERS_BONUS_H

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