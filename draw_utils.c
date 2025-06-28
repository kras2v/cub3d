/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:24:32 by kvalerii          #+#    #+#             */
/*   Updated: 2025/06/25 20:38:28 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	clear_display(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = WIDTH;
		while (x < WIDTH * 2)
		{
			my_mlx_pixel_put(&(data->img), x, y, BLACK);
			x++;
		}
		y++;
	}
}

void	draw_horizontal(t_data *data, t_fvector a, t_fvector b, t_colors color)
{
	int	dx;
	int	dy;
	int	p;
	int	y;
	int	x;
	int	dir;

	if (a.x > b.x)
	{
		swap_points(&a, &b);
	}
	dx = b.x - a.x;
	dy = b.y - a.y;
	if (dy < 0)
	{
		dir = -1;
	}
	else
	{
		dir = 1;
	}
	dy *= dir;
	if (dx != 0)
	{
		x = 0;
		y = a.y;
		p = 2 * dy - dx;
		while (x < dx + 1)
		{
			if (a.x + x >= 0 && a.x + x < WIDTH && y >= 0 && y < HEIGHT)
				my_mlx_pixel_put(&(data->img), a.x + x, y, color);
			if (p >= 0)
			{
				y += dir;
				p = p - 2 * dx;
			}
			p = p + 2 * dy;
			x++;
		}
	}
}

void	draw_vertical(t_data *data, t_fvector a, t_fvector b, t_colors color)
{
	int	dx;
	int	dy;
	int	p;
	int	y;
	int	x;
	int	dir;

	if (a.y > b.y)
	{
		swap_points(&a, &b);
	}
	dx = b.x - a.x;
	dy = b.y - a.y;
	if (dx < 0)
	{
		dir = -1;
	}
	else
	{
		dir = 1;
	}
	dx *= dir;
	if (dy != 0)
	{
		y = 0;
		x = a.x;
		p = 2 * dx - dy;
		while (y < dy + 1)
		{
			if (y + a.y >= 0 && y + a.y < HEIGHT && x >= 0 && x < WIDTH)
				my_mlx_pixel_put(&(data->img), x, y + a.y, color);
			if (p >= 0)
			{
				x += dir;
				p = p - 2 * dy;
			}
			p = p + 2 * dx;
			y++;
		}
	}
}

void	draw_line(t_data *data, t_fvector a, t_fvector b, t_colors color)
{
	if (fabs(b.x - a.x) >= fabs(b.y - a.y))
	{
		draw_horizontal(data, a, b, color);
	}
	else
	{
		draw_vertical(data, a, b, color);
	}
}
