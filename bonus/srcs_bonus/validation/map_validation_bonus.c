/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:01:26 by eklymova          #+#    #+#             */
/*   Updated: 2025/07/29 12:31:24 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_bonus.h"

static bool	pathes_loaded(t_data *data)
{
	return (data->texture_names[N] && data->texture_names[E]
		&& data->texture_names[S] && data->texture_names[W]);
}

bool	colors_added(t_data *data)
{
	return (data->c > -1 && data->f > -1);
}

bool	is_map_valid(t_data	*data)
{
	if (!pathes_loaded(data) || !colors_added(data))
		return (close_on_error(data, MISSING_ATTR), false);
	if (!char_counter(data))
		return (close_on_error(data, PLAYER_ERR), false);
	if (!invalid_char(data))
		return (close_on_error(data, INVALID_CHAR), false);
	if (!check_map_walls(data))
		return (close_on_error(data, MAP_UNCLOSED_ERR), false);
	return (true);
}
