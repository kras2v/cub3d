/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:19:21 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/17 12:19:28 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

int	display(t_data *data)
{
	dda(data);
	draw_map_fill(data);
	draw_flashlight(data);
	draw_player(data);
	update_sprite(data);
	draw_sprite(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
	return (1);
}
