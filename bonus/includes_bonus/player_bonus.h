/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:55:52 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/29 12:31:34 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_BONUS_H
# define PLAYER_BONUS_H

# include "math_helpers_bonus.h"

# define PLAYER_SIZE 8

typedef enum e_move
{
	UP,
	LEFT,
	DOWN,
	RIGHT,
}	t_move;

typedef struct s_flash_params
{
	t_fvector	player_pos;
	int			map_start_x;
	int			map_start_y;
	double		fov;
	int			rays;
	double		step_angle;
	double		start;
}	t_flash_params;

typedef struct s_player_side
{
	t_point	up;
	t_point	down;
}	t_player_side;

typedef struct s_player
{
	t_fvector		position;
	t_fvector		direction;
	t_fvector		plane;
	t_player_side	right_side;
	t_player_side	left_side;
}	t_player;

#endif