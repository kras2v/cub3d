/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_game_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:19:21 by kvalerii          #+#    #+#             */
/*   Updated: 2025/08/04 16:17:49 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_bonus.h"

int	display(t_data *data)
{
	dda(data);
	draw_map_fill(data);
	draw_flashlight(data);
	draw_player(data);
	update_sprite(data);
	draw_sprite(data);
	close_door(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
	return (1);
}
