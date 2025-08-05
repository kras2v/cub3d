/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:18:49 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/29 12:25:15 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

bool	validate_user_input(t_data *data, int argc, char **args)
{
	if (argc != 2)
		return (close_on_error(data, WRONG_ARGC), 1);
	is_file_name_valid(data, args[1]);
	data->script = read_map(data, args[1]);
	read_actual_map(data, args[1]);
	is_script_valid(data);
	is_map_valid(data);
	return (true);
}
