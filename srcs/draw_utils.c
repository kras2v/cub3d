/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:24:32 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/16 20:03:43 by valeriia         ###   ########.fr       */
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
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&(data->img), x, y, BLACK);
			x++;
		}
		y++;
	}
}

t_colors find_color(t_data *data, char *input_clr)
{
	t_colors	color;
	int			r;
	int			g;
	int			b;

	data->lekkereclrs = ft_split(input_clr, ',');
	if (!data->lekkereclrs || !data->lekkereclrs[0] || !data->lekkereclrs[1] || !data->lekkereclrs[2])
	{
		close_event(data);
		return (0);
	}
	r = ft_atoi(data->lekkereclrs[0]);
	g = ft_atoi(data->lekkereclrs[1]);
	b = ft_atoi(data->lekkereclrs[2]);
	if (r == -1 || b == -1 || g == -1)
	{
		//!ADD ERROR
		printf("Range from 0 to 255\n");
		close_event(data);
	}
	if (data->lekkereclrs)
		free_double_arr(data->lekkereclrs);
	data->lekkereclrs = NULL;
	color = (r << 16) | (g << 8) | b;
	return (color);
}
