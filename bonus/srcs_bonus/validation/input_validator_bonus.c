/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:18:49 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/23 17:18:24 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda_bonus.h"

bool	validate_user_input(t_data *data, int argc, char **args)
{
	if (argc != 2)
		return (close_on_error(data, WRONG_ARGC), 1);
	is_file_name_valid(data, args[1]);
	data->script = read_map(data, args[1]);
	is_script_valid(data);
	data->texture_names[D] = DOOR_PATH;
	is_map_valid(data);
	return (true);
}
