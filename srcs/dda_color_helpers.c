/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_color_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:52:15 by valeriia          #+#    #+#             */
/*   Updated: 2025/07/16 20:39:42 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	get_wall_start_and_end(
	int line_height,
	int *start_pixel,
	int *end_pixel
)
{
	*start_pixel = -line_height / 2 + HEIGHT / 2;
	if (*start_pixel < 0)
		*start_pixel = 0;
	*end_pixel = line_height / 2 + HEIGHT / 2;
	if (*end_pixel >= HEIGHT)
		*end_pixel = HEIGHT - 1;
}

void	draw_floor(
	t_data *data,
	int end_pixel,
	t_colors color,
	int x
)
{
	t_fvector	screen_bottom;
	t_fvector	start_point;

	screen_bottom.x = x;
	screen_bottom.y = HEIGHT - 1;
	start_point.x = x;
	start_point.y = end_pixel;
	draw_line(data, screen_bottom, start_point, color);
}

void	draw_celing(
	t_data *data,
	int start_pixel,
	t_colors color,
	int x
)
{
	t_fvector	screen_top;
	t_fvector	start_point;

	screen_top.x = x;
	screen_top.y = 0;
	start_point.x = x;
	start_point.y = start_pixel;
	draw_line(data, screen_top, start_point, color);
}