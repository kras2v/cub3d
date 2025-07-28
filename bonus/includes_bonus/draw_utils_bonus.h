/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:19:11 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/28 12:23:22 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_UTILS_BONUS_H
# define DRAW_UTILS_BONUS_H

# include "player.h"
# include "sprite.h"
# include "dda.h"
# include <sys/time.h>

//BRESENHAM
void	increase_stepping(int *p, int dir,
			t_coordinates *coords, t_coordinates delta);
void	swap_axis(t_fvector *a);
void	get_direction(int *dir, int *delta);
void	assign_delta_coords(t_coordinates *delta, t_fvector *a, t_fvector *b);

void	my_mlx_pixel_put(t_image *data, int x, int y, int color);

#endif
