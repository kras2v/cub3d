/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:58:24 by eklymova          #+#    #+#             */
/*   Updated: 2025/07/19 21:33:49 by eklymova        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	find_sprite_pos(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (data->map[i][j] == '2')
			{
				data->sprite->x = j + 0.5;
				data->sprite->y = i + 0.5;
				data->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

long int	time_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

uint32_t	get_pixel_color(t_texture *texture, int x, int y)
{
	char	*pixel;
	int		offset;

	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (0);
	offset = y * texture->image.line_length
		+ x * (texture->image.bits_per_pixel / 8);
	pixel = texture->image.addr + offset;
	return (*(uint32_t *)pixel);
}

void	update_sprite(t_data *data)
{
	long int	now;

	now = time_now();
	if (now - data->sprite->frame_timer >= data->sprite->frame_delay)
	{
		data->sprite->cur_frame++;
		if (data->sprite->cur_frame >= 2)
			data->sprite->cur_frame = 0;
		data->sprite->frame_timer = now;
	}
}

t_texture	*load_sprite_texture(t_data *data, const char *path)
{
	t_texture	*texture;

	texture = ft_calloc(2, sizeof(t_texture));
	if (!texture)
		return (close_event(data), NULL);
	texture->image.ptr = mlx_xpm_file_to_image(data->mlx, (char *)path,
			&texture->width, &texture->height);
	if (!texture->image.ptr)
		return (close_event(data), NULL);
	texture->image.addr = mlx_get_data_addr(texture->image.ptr,
			&texture->image.bits_per_pixel,
			&texture->image.line_length,
			&texture->image.endian);
	if (!texture->image.addr)
		return (close_event(data), NULL);
	return (texture);
}
