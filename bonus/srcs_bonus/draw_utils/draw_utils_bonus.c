/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:24:32 by kvalerii          #+#    #+#             */
/*   Updated: 2025/08/05 13:29:46 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_bonus.h"

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

t_colors	find_color(t_data *data, char *input_clr)
{
	char		**lekkereclrs;
	t_colors	color;
	int			r;
	int			g;
	int			b;

	lekkereclrs = ft_split(input_clr, ',');
	if (!lekkereclrs || !lekkereclrs[0] || !lekkereclrs[1]
		|| !lekkereclrs[2] || lekkereclrs[3])
		return (free_double_arr(lekkereclrs),
			close_on_error(data, COLOR_ERR), 0);
	r = ft_atoi(lekkereclrs[0]);
	g = ft_atoi(lekkereclrs[1]);
	b = ft_atoi(lekkereclrs[2]);
	if (r == -1 || b == -1 || g == -1)
	{
		free_double_arr(lekkereclrs);
		return (close_on_error(data, COLOR_ERR), 0);
	}
	free_double_arr(lekkereclrs);
	lekkereclrs = NULL;
	color = (r << 16) | (g << 8) | b;
	return (color);
}
