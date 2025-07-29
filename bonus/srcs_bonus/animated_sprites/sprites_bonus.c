/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:09:40 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/29 12:31:16 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_bonus.h"

int	init_sprite(t_data *data)
{
	data->sprite = ft_calloc(1, sizeof(t_sprite));
	if (!data->sprite)
		return (printf("Failed to allocate sprite\n"), close_event(data));
	data->sprite->tex = ft_calloc(2, sizeof(t_texture_params *));
	if (!data->sprite->tex)
		return (printf("Failed to allocate texture array\n"),
			close_event(data));
	data->sprite->tex[0] = load_sprite_texture(data, "./walls/xpm/ducky1.xpm");
	data->sprite->tex[1] = load_sprite_texture(data, "./walls/xpm/ducky2.xpm");
	if (!data->sprite->tex[0] || !data->sprite->tex[1])
		return (printf("Failed to load sprite textures\n"), close_event(data));
	data->sprite->s_width = 48;
	data->sprite->s_height = 48;
	data->sprite->cur_frame = 0;
	data->sprite->frame_timer = 0.0;
	data->sprite->frame_delay = 200.0;
	find_sprite_pos(data);
	return (1);
}

void	while_row(t_data *data, int y, int stripe, int tex_x)
{
	int		tex_y;
	double	d;

	d = (y - data->sprite->v_move_win) * 256
		- HEIGHT * 128 + data->sprite->s_height * 128;
	tex_y = ((d
				* data->sprite->tex[data->sprite->cur_frame]->height)
			/ data->sprite->s_height) / 256;
	data->sprite->color
		= get_pixel_color(data->sprite->tex[data->sprite->cur_frame],
			tex_x, tex_y);
	if ((data->sprite->color & 0x00FFFFFF) != 0)
		((uint32_t *)data->img.addr)[y * WIDTH + stripe] = data->sprite->color;
}

void	draw_by_strips(t_data *data)
{
	int		stripe;
	int		y;
	int		tex_x;

	stripe = data->sprite->start_x;
	while (stripe < data->sprite->end_x)
	{
		tex_x = (int)(256 * (stripe - (-(data->sprite->s_width)
						/ 2 + data->sprite->s_win_x))
				* data->sprite->tex[data->sprite->cur_frame]->width)
			/ data->sprite->s_width / 256;
		if (data->sprite->trnform_y > 0 && stripe > 0
			&& stripe < WIDTH
			&& data->sprite->trnform_y < data->z_buffer[stripe])
		{
			y = (int)data->sprite->start_y;
			while (y < data->sprite->end_y)
			{
				while_row(data, y, stripe, tex_x);
				y++;
			}
		}
		stripe++;
	}
}

void	find_start_end(t_data *data)
{
	data->sprite->start_y = -data->sprite->s_height / 2
		+ HEIGHT / 2 + data->sprite->v_move_win;
	if (data->sprite->start_y < 0)
		data->sprite->start_y = 0;
	data->sprite->end_y = data->sprite->s_height / 2
		+ HEIGHT / 2 + data->sprite->v_move_win;
	if (data->sprite->end_y >= HEIGHT)
		data->sprite->end_y = HEIGHT - 1;
	data->sprite->start_x = -data->sprite->s_width / 2 + data->sprite->s_win_x;
	if (data->sprite->start_x < 0)
		data->sprite->start_x = 0;
	data->sprite->end_x = data->sprite->s_width / 2 + data->sprite->s_win_x;
	if (data->sprite->end_x >= WIDTH)
		data->sprite->end_x = WIDTH - 1;
}

void	draw_sprite(t_data *data)
{
	data->sprite->v_s_x = data->sprite->x - data->player.position.x;
	data->sprite->v_s_y = data->sprite->y - data->player.position.y;
	data->sprite->inv_det = 1.0 / (data->player.plane.x
			* data->player.direction.y - data->player.direction.x
			* data->player.plane.y);
	data->sprite->trnform_x = data->sprite->inv_det
		* (data->player.direction.y * data->sprite->v_s_x
			- data->player.direction.x * data->sprite->v_s_y);
	data->sprite->trnform_y = data->sprite->inv_det
		* (-(data->player.plane.y) * data->sprite->v_s_x
			+ data->player.plane.x * data->sprite->v_s_y);
	data->sprite->s_win_x = ((WIDTH / 2)
			* (1 + data->sprite->trnform_x / data->sprite->trnform_y));
	data->sprite->v_move_win = (int)(VERTICAL_MOVE / data->sprite->trnform_y);
	data->sprite->s_height = fabs(HEIGHT / data->sprite->trnform_y);
	data->sprite->s_width = fabs(HEIGHT / data->sprite->trnform_y);
	find_start_end(data);
	draw_by_strips(data);
}
