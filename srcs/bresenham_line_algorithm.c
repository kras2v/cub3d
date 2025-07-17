/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line_algorithm.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:52:37 by valeriia          #+#    #+#             */
/*   Updated: 2025/07/17 17:42:24 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	put_pixel_on_axis(
	t_data *data,
	int is_horizontal,
	t_coordinates coords,
	t_line line
)
{
	if (is_horizontal == false)
	{
		if (coords.y + line.a.y >= 0
			&& coords.y + line.a.y < HEIGHT
			&& coords.x >= 0
			&& coords.x < WIDTH)
			my_mlx_pixel_put(&(data->img), coords.x,
				coords.y + line.a.y, line.color);
	}
	else
	{
		if (line.a.y + coords.y >= 0
			&& line.a.y + coords.y < WIDTH
			&& coords.x >= 0
			&& coords.x < HEIGHT)
			my_mlx_pixel_put(&(data->img), line.a.y + coords.y,
				coords.x, line.color);
	}
}

void	bresenham(t_data *data, t_line line, int is_horizontal)
{
	t_coordinates	delta;
	t_coordinates	coords;
	int				p;
	int				dir;

	assign_delta_coords(&delta, &line.a, &line.b);
	get_direction(&dir, &delta.x);
	if (delta.y != 0)
	{
		coords.y = 0;
		coords.x = line.a.x;
		p = 2 * delta.x - delta.y;
		while (coords.y < delta.y + 1)
		{
			put_pixel_on_axis(data, is_horizontal, coords, line);
			increase_stepping(&p, dir, &coords, delta);
			p = p + 2 * delta.x;
			coords.y++;
		}
	}
}

void	draw_line(t_data *data, t_fvector a, t_fvector b, t_colors color)
{
	t_line		line;

	line.a = a;
	line.b = b;
	line.color = color;
	if (fabs(line.b.x - line.a.x) >= fabs(line.b.y - line.a.y))
	{
		swap_axis(&line.a);
		swap_axis(&line.b);
		bresenham(data, line, true);
	}
	else
	{
		bresenham(data, line, false);
	}
}
