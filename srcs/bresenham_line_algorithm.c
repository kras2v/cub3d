/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line_algorithm.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:52:37 by valeriia          #+#    #+#             */
/*   Updated: 2025/07/16 19:53:56 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	get_direction(int *dir, int *delta)
{
	if ((*delta) < 0)
	{
		*dir = -1;
	}
	else
	{
		*dir = 1;
	}
	(*delta) *= (*dir);
}

void	assign_delta_coords(t_coordinates *delta, t_fvector *a, t_fvector *b, bool is_horizontal)
{
	if ((is_horizontal && a->x > b->x) || (!is_horizontal && a->y > b->y))
	{
		swap_points(a, b);
	}
	delta->x = b->x - a->x;
	delta->y = b->y - a->y;
}

void	draw_horizontal(t_data *data, t_fvector a, t_fvector b, t_colors color)
{
	t_coordinates	delta;
	t_coordinates	coords;
	int	p;
	int	dir;

	assign_delta_coords(&delta, &a, &b, true);
	get_direction(&dir, &delta.y);
	if (delta.x != 0)
	{
		coords.x = 0;
		coords.y = a.y;
		p = 2 * delta.y - delta.x;
		while (coords.x < delta.x + 1)
		{
			if (a.x + coords.x >= 0 && a.x + coords.x < WIDTH && coords.y >= 0 && coords.y < HEIGHT)
				my_mlx_pixel_put(&(data->img), a.x + coords.x, coords.y, color);
			if (p >= 0)
			{
				coords.y += dir;
				p = p - 2 * delta.x;
			}
			p = p + 2 * delta.y;
			coords.x++;
		}
	}
}

void	draw_vertical(t_data *data, t_fvector a, t_fvector b, t_colors color)
{
	t_coordinates	delta;
	t_coordinates	coords;
	int	p;
	int	dir;

	assign_delta_coords(&delta, &a, &b, false);
	get_direction(&dir, &delta.x);
	if (delta.y != 0)
	{
		coords.y = 0;
		coords.x = a.x;
		p = 2 * delta.x - delta.y;
		while (coords.y < delta.y + 1)
		{
			if (coords.y + a.y >= 0 && coords.y + a.y < HEIGHT && coords.x >= 0 && coords.x < WIDTH)
				my_mlx_pixel_put(&(data->img), coords.x, coords.y + a.y, color);
			if (p >= 0)
			{
				coords.x += dir;
				p = p - 2 * delta.y;
			}
			p = p + 2 * delta.x;
			coords.y++;
		}
	}
}

void	draw_line(t_data *data, t_fvector a, t_fvector b, t_colors color)
{
	if (a.x > b.x)
			swap_points(&a, &b);
	if (fabs(b.x - a.x) >= fabs(b.y - a.y))
	{
		draw_horizontal(data, a, b, color);
	}
	else
	{
		draw_vertical(data, a, b, color);
	}
}
