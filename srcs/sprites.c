/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:09:40 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/22 14:09:43 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "dda.h"

int	init_sprite(t_data *data)
{
	data->sprite = ft_calloc(1, sizeof(t_sprite));
	if (!data->sprite)
		return(printf("Failed to allocate sprite\n"), close_event(data));
	data->sprite->texture = ft_calloc(2, sizeof(t_texture *));
	if (!data->sprite->texture)
		return(printf("Failed to allocate texture array\n"), close_event(data));
	data->sprite->texture[0] = load_sprite_texture(data, "./walls/xpm/ducky-idle1.xpm");
	data->sprite->texture[1] = load_sprite_texture(data, "./walls/xpm/ducky-idle2.xpm");
	if (!data->sprite->texture[0] || !data->sprite->texture[1])
		return(printf("Failed to load sprite textures\n"), close_event(data));
	data->sprite->sprite_width = 48;
	data->sprite->sprite_height = 48;
	data->sprite->current_frame = 0;
	data->sprite->frame_timer = 0.0;
	data->sprite->frame_delay = 200.0;
	find_sprite_pos(data);
	return (1);
}

void	draw_by_strips(t_data *data)
{
	int		stripe;
	int		y;
	double	d;
	int 	texX;
	int 	texY;
	uint32_t color;
	stripe = data->sprite->draw_start_x;
	while (stripe < data->sprite->draw_end_x)
	{
		texX = (int)(256 * (stripe - (-(data->sprite->sprite_width) / 2 + data->sprite->spriteScreenX)) * data->sprite->texture[data->sprite->current_frame]->width) / data->sprite->sprite_width / 256;
		if (data->sprite->transformY > 0 && stripe > 0 && stripe < WIDTH && data->sprite->transformY < data->ZBuffer[stripe])
		{
			y = (int)data->sprite->draw_start_y;
			while(y < data->sprite->draw_end_y)
			{
				d = (y - data->sprite->vMoveScreen) * 256 - HEIGHT * 128 + data->sprite->sprite_height * 128;
				texY = ((d * data->sprite->texture[data->sprite->current_frame]->height) / data->sprite->sprite_height) / 256;
				color = get_pixel_color(data->sprite->texture[data->sprite->current_frame], texX, texY);
				if ((color & 0x00FFFFFF) != 0)
					((uint32_t *)data->img.addr)[y * WIDTH + stripe] = color;
				y++;
			}
		}
		stripe++;
	}
}

void	draw_sprite(t_data *data)
{
	data->sprite->VspriteX = data->sprite->x - data->player.position.x;
	data->sprite->VspriteY = data->sprite->y - data->player.position.y; // vector from player to sprite
	data->sprite->invDet = 1.0 / (data->player.plane.x * data->player.direction.y - data->player.direction.x * data->player.plane.y);
	data->sprite->transformX = data->sprite->invDet * (data->player.direction.y * data->sprite->VspriteX - data->player.direction.x * data->sprite->VspriteY); // xcoordinate sprite in camera space
	data->sprite->transformY = data->sprite->invDet * (-(data->player.plane.y) * data->sprite->VspriteX + data->player.plane.x * data->sprite->VspriteY); // distance betw player and sprite (deep)
	data->sprite->spriteScreenX = ((WIDTH / 2) * (1 + data->sprite->transformX / data->sprite->transformY)); // center 
	data->sprite->vMoveScreen = (int)(VERTICAL_MOVE / data->sprite->transformY);
	data->sprite->sprite_height = fabs(HEIGHT / data->sprite->transformY); // Height of the sprite (the closer the bigger)
	data->sprite->sprite_width = fabs(HEIGHT / data->sprite->transformY); // width (often the same as height)
		data->sprite->draw_start_y = -data->sprite->sprite_height / 2 + HEIGHT / 2 + data->sprite->vMoveScreen;
	if (data->sprite->draw_start_y < 0)
		data->sprite->draw_start_y = 0;
	data->sprite->draw_end_y = data->sprite->sprite_height / 2 + HEIGHT / 2 + data->sprite->vMoveScreen;
	if (data->sprite->draw_end_y >= HEIGHT)
		data->sprite->draw_end_y = HEIGHT - 1;
	data->sprite->draw_start_x = -data->sprite->sprite_width / 2 + data->sprite->spriteScreenX;
	if (data->sprite->draw_start_x < 0)
		data->sprite->draw_start_x = 0;
	data->sprite->draw_end_x = data->sprite->sprite_width / 2 + data->sprite->spriteScreenX;
	if (data->sprite->draw_end_x >= WIDTH)
		data->sprite->draw_end_x = WIDTH - 1;
	draw_by_strips(data);
}

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

void	update_sprite(t_data *data)
{
	long int	now;

	now = time_now();
	if (now - data->sprite->frame_timer >= data->sprite->frame_delay)
	{
		data->sprite->current_frame++;
		if (data->sprite->current_frame >= 2)
			data->sprite->current_frame = 0;
		data->sprite->frame_timer = now;
	}
}
