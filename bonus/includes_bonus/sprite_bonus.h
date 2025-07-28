/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:04:26 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/28 12:15:10 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_BONUS_H
# define SPRITE_BONUS_H

# include "texture.h"
# include <stdint.h>

# define VERTICAL_MOVE 0.5

typedef struct s_sprite
{
	t_texture_params	**tex;
	int					cur_frame;
	long int			frame_timer;
	double				frame_delay;
	int					s_width;
	int					s_height;
	double				x;
	double				y;
	double				v_s_x;
	double				v_s_y;
	double				trnform_x;
	double				trnform_y;
	double				s_win_x;
	double				start_x;
	double				start_y;
	double				end_x;
	double				end_y;
	int					v_move_win;
	double				inv_det;
	uint32_t			color;
}	t_sprite;

#endif