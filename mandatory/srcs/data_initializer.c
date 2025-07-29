/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_initializer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:16:21 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/29 12:45:55 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

int	initialize_data(t_data *data)
{
	int	x;

	x = 0;
	data->map_height = 0;
	data->map_width = 0;
	data->c = -1;
	data->f = -1;
	data->texture_params = NULL;
	data->script = NULL;
	data->mlx = NULL;
	data->map = NULL;
	data->texture_names = ft_calloc(5, sizeof(char *));
	while (x < WIDTH)
	{
		data->normalized_x[x] = (2.0 * (double)x / (double)WIDTH) - 1.0;
		x++;
	}
	return (0);
}
