/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:55:52 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/29 12:29:45 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDA_BONUS_H
# define DDA_BONUS_H

# include <stdbool.h>
# include "math_helpers_bonus.h"
# include "colors_bonus.h"

# define PI 3.14159265358979323846
# define FOV 0.66
# define MOVE_SPEED 0.3
# define ROT_SPEED 0.3

typedef enum e_side
{
	VERTICAL,
	HORIZONTAL
}	t_side;

typedef struct s_dda_parameters
{
	t_point			player_position_in_cell;
	bool			door_in_fov;
	double			distance_to_wall;
	t_coordinates	player_cell;
	t_fvector		ray;
	t_fvector		initial_step;
	t_fvector		fixed_step;
	t_coordinates	step;
	t_side			side;
	int				start_pixel;
	int				end_pixel;
	int				x;
}	t_dda_parameters;

typedef struct s_line
{
	t_fvector	a;
	t_fvector	b;
	t_colors	color;
}	t_line;

#endif