/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:28:10 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/22 16:26:15 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

int	main(int argc, char **args)
{
	t_data	data;

	initialize_data(&data);
	validate_user_input(&data, argc, args);
	start_mlx(&data);
	init_player(&data);
	init_sprite(&data);
	mlx_loop_hook(data.mlx, &display, &data);
	mlx_loop(data.mlx);
	close_event(&data);
	return (0);
}
