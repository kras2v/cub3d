/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:03:35 by valeriia          #+#    #+#             */
/*   Updated: 2025/07/22 14:04:57 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

static double	get_x_coordinates_on_texture(
	int texture_width,
	t_dda_parameters *dda_parameters
)
{
	double	wall_hit_coord;

	if (dda_parameters->side == VERTICAL)
		wall_hit_coord = dda_parameters->player_position_in_cell.y
			+ dda_parameters->distance_to_wall * dda_parameters->ray.y;
	else
		wall_hit_coord = dda_parameters->player_position_in_cell.x
			+ dda_parameters->distance_to_wall * dda_parameters->ray.x;
	wall_hit_coord -= floor(wall_hit_coord);
	return ((int)(wall_hit_coord * (double)texture_width));
}

void	get_wall_direction(
	t_direction *wall_dir,
	t_dda_parameters *dda_parameters
)
{
	if (dda_parameters->door_in_fov)
		(*wall_dir = D);
	else if (dda_parameters->side == VERTICAL && dda_parameters->ray.x < 0)
		(*wall_dir) = E;
	else if (dda_parameters->side == VERTICAL && dda_parameters->ray.x > 0)
		(*wall_dir) = W;
	else if (dda_parameters->side == HORIZONTAL && dda_parameters->ray.y < 0)
		(*wall_dir) = N;
	else if (dda_parameters->side == HORIZONTAL && dda_parameters->ray.y > 0)
		(*wall_dir) = S;
}

void	draw_texture_pixel(
	t_dda_parameters *dda_parameters,
	t_data *data,
	int x,
	double start_y_coordinate
)
{
	char			*offset;
	unsigned int	color;
	t_coordinates	texture;
	t_direction		wall_dir;

	get_wall_direction(&wall_dir, dda_parameters);
	texture.x = get_x_coordinates_on_texture(
			data->texture[wall_dir].width,
			dda_parameters
			);
	offset = data->texture[wall_dir].image.addr
		+ ((int)start_y_coordinate
			* data->texture[wall_dir].image.line_length + texture.x
			* data->texture[wall_dir].image.bits_per_pixel / CHAR_BIT);
	color = *(unsigned int *)offset;
	my_mlx_pixel_put(&data->img, x, dda_parameters->start_pixel, color);
}

void	draw_textures(
	t_data *data,
	t_dda_parameters *dda_parameters,
	int x
)
{
	int				wall_height;
	double			y_increase_step;
	double			start_y_coordinate_on_texture;

	wall_height = (int)(HEIGHT / dda_parameters->distance_to_wall);
	y_increase_step = (double)data->texture->height / (double)wall_height;
	get_wall_start_and_end(wall_height,
		&dda_parameters->start_pixel, &dda_parameters->end_pixel);
	start_y_coordinate_on_texture = (dda_parameters->start_pixel
			- HEIGHT / 2 + wall_height / 2) * y_increase_step;
	draw_celing(data, dda_parameters->start_pixel, data->c, x);
	draw_floor(data, dda_parameters->end_pixel, data->f, x);
	while (dda_parameters->start_pixel < dda_parameters->end_pixel)
	{
		start_y_coordinate_on_texture += y_increase_step;
		draw_texture_pixel(
			dda_parameters,
			data, x,
			start_y_coordinate_on_texture
			);
		dda_parameters->start_pixel++;
	}
}

void	dda(t_data *data)
{
	int					x;
	t_dda_parameters	dda_parameters;

	x = 0;
	get_player_position_on_map(data, &dda_parameters.player_position_in_cell);
	get_player_cell(
		dda_parameters.player_position_in_cell,
		&dda_parameters.player_cell);
	while (x < WIDTH)
	{
		dda_parameters.door_in_fov = false;
		get_x_ray_coordinates(x, data, &dda_parameters.ray);
		get_fixed_step_between_lines(
			dda_parameters.ray,
			&dda_parameters.fixed_step);
		get_direction_step(&dda_parameters);
		get_initial_step(&dda_parameters);
		dda_parameters.distance_to_wall = find_distance_to_wall(data,
				&dda_parameters,
				dda_parameters.player_cell);
		draw_textures(data, &dda_parameters, x);
		x++;
	}
}
