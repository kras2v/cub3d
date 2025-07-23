/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:24:32 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/23 15:26:37 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length
			+ x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_display(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = WIDTH;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&(data->img), x, y, BLACK);
			x++;
		}
		y++;
	}
}

//!ADD ERROR
t_colors	find_color(t_data *data, char *input_clr)
{
	char		**lekkereclrs;
	t_colors	color;
	int			r;
	int			g;
	int			b;

	lekkereclrs = ft_split(input_clr, ',');
	if (!lekkereclrs)
		return (close_event(data), 0);
	if (!lekkereclrs[0] || !lekkereclrs[1] || !lekkereclrs[2])
		return (free_double_arr(lekkereclrs), 0);
	r = ft_atoi(lekkereclrs[0]);
	g = ft_atoi(lekkereclrs[1]);
	b = ft_atoi(lekkereclrs[2]);
	if (r == -1 || b == -1 || g == -1)
	{
		free_double_arr(lekkereclrs);
		close_on_error(data, COLOR_ERR);
	}
	free_double_arr(lekkereclrs);
	lekkereclrs = NULL;
	color = (r << 16) | (g << 8) | b;
	return (color);
}
