/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:03:35 by valeriia          #+#    #+#             */
/*   Updated: 2025/07/11 16:12:03 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	get_player_position_on_map(
	t_data *data,
	t_point *player_position_in_cell)
{
	player_position_in_cell->x = (data->player.position.x);
	player_position_in_cell->y = (data->player.position.y);
}

void	get_player_cell(
	t_point player_position_in_cell,
	t_coordinates *player_cell)
{
	player_cell->x = (int)player_position_in_cell.x;
	player_cell->y = (int)player_position_in_cell.y;
}

void	get_initial_step(
	t_fvector ray,
	t_point player_position_in_cell,
	t_coordinates player_cell,
	t_fvector *initial_step,
	t_fvector fixed_step,
	t_coordinates *step
	)
{
	if (ray.x < 0)
	{
		step->x = -1;
		initial_step->x = (player_position_in_cell.x - (double)player_cell.x) * fixed_step.x;
	}
	else
	{
		step->x = 1;
		initial_step->x = ((double)player_cell.x + 1.0 - player_position_in_cell.x) * fixed_step.x;
	}
	if (ray.y < 0)
	{
		step->y = -1;
		initial_step->y = (player_position_in_cell.y - (double)player_cell.y) * fixed_step.y;
	}
	else
	{
		step->y = 1;
		initial_step->y = ((double)player_cell.y + 1.0 - player_position_in_cell.y) * fixed_step.y;
	}
}

void	get_fixed_step_between_lines(
	t_fvector ray,
	t_fvector *fixed_step
	)
{
	fixed_step->x = INFINITY;
	if (ray.x != 0)
	{
		fixed_step->x = fabs(1.0 / ray.x);
	}
	fixed_step->y = INFINITY;
	if (ray.y != 0)
	{
		fixed_step->y = fabs(1.0 / ray.y);
	}
}

void	get_x_ray_coordinates(
	int x,
	t_data *data,
	t_fvector *ray
	)
{
	ray->x = data->player.direction.x + data->player.plane.x * data->normilized_x[x];
	ray->y = data->player.direction.y + data->player.plane.y * data->normilized_x[x];
}

// void	draw_rays_on_map(t_data *data, t_coordinates player_cell)
// {
// 	t_fvector player_pos;
// 	t_fvector ray_end;
// 	int map_start_x = (int)data->player.position.x - MINIMAP_RADIUS;
// 	int map_start_y = (int)data->player.position.y - MINIMAP_RADIUS ;

// 	player_pos.x = ((data->player.position.x) - map_start_x) * MINI_TILE;
// 	player_pos.y = ((data->player.position.y) - map_start_y) * MINI_TILE;

// 	ray_end.x = (player_cell.x - map_start_x) * MINI_TILE;
// 	ray_end.y = (player_cell.y - map_start_y) * MINI_TILE;

//  	// draw_line(data, player_pos, ray_end, WHITE);
// }

double	find_distance_to_wall(
	t_data *data,
	t_fvector fixed_step,
	t_fvector *initial_step,
	t_side *side,
	t_coordinates *step,
	t_coordinates player_cell
	)
{
	int	hit;

	hit = false;
	*side = VERTICAL;
	while (hit == false)
	{
		if (initial_step->x < initial_step->y)
		{
			initial_step->x += fixed_step.x;
			player_cell.x += step->x;
			*side = VERTICAL;
		}
		else
		{
			initial_step->y += fixed_step.y;
			player_cell.y += step->y;
			*side = HORIZONTAL;
		}
		if (data->map[player_cell.y][player_cell.x] == WALL && is_direction(data->map[player_cell.y][player_cell.x]) == false)
			hit = true;
	}
	// draw_rays_on_map(data, player_cell);
	if (*side == VERTICAL)
		return (initial_step->x - fixed_step.x);
	return (initial_step->y - fixed_step.y);
}

void	get_start_and_end_draw_pixels(
	int line_height,
	int *start_pixel,
	int *end_pixel
)
{
	*start_pixel = -line_height / 2 + HEIGHT / 2;
	if (*start_pixel < 0)
		*start_pixel = 0;
	*end_pixel = line_height / 2 + HEIGHT / 2;
	if (*end_pixel >= HEIGHT)
		*end_pixel = HEIGHT - 1;
}

void	draw_floor(
	t_data *data,
	int end_pixel,
	t_colors color,
	int x
)
{
	t_fvector	screen_bottom;
	t_fvector	start_point;

	screen_bottom.x = x;
	screen_bottom.y = HEIGHT - 1;
	start_point.x = x;
	start_point.y = end_pixel;
	draw_line(data, screen_bottom, start_point, color);
}

void	draw_celing(
	t_data *data,
	int start_pixel,
	t_colors color,
	int x
)
{
	t_fvector	screen_top;
	t_fvector	start_point;

	screen_top.x = x;
	screen_top.y = 0;
	start_point.x = x;
	start_point.y = start_pixel;
	draw_line(data, screen_top, start_point, color);
}

t_colors find_color(t_data *data, char part)
{
	t_colors	color;
	char		*input_clr;
	int			r;
	int			g;
	int			b;

	if (part == 'F')
		input_clr = data->F;
	else
		input_clr = data->C;
	data->lekkereclrs = ft_split(input_clr, ',');
	if (!data->lekkereclrs || !data->lekkereclrs[0] || !data->lekkereclrs[1] || !data->lekkereclrs[2])
	{
		close_event(data);
		return (0);
	}
	r = ft_atoi(data->lekkereclrs[0]);
	g = ft_atoi(data->lekkereclrs[1]);
	b = ft_atoi(data->lekkereclrs[2]);
	if (r == -1 | b == -1 | g == -1)
	{
		printf("Range from 0 to 255\n");
		close_event(data);
	}
	if (data->lekkereclrs)
		free_double_arr(data->lekkereclrs);
	data->lekkereclrs = NULL;
	color = (r << 16) | (g << 8) | b;
	return (color);
}

void	draw_line_text(
	t_data *data,
	t_side side,
	int x,
	t_fvector ray,
	t_point player_position_in_cell,
	// t_coordinates player_cell,
	double			distance_to_wall
)
{
	(void)player_position_in_cell;
	(void)ray;
	int				line_height;
	double			y_increase_step;
	int				start_pixel;
	int				end_pixel;
	double			wall_hit_coord;
	char			*offset;
	unsigned int	color;
	double			position_on_texture;
	t_coordinates	texture;
	int				text_num;

	line_height = (int)(HEIGHT / distance_to_wall);
	get_start_and_end_draw_pixels(line_height, &start_pixel, &end_pixel);
	if (side == VERTICAL)
		wall_hit_coord = player_position_in_cell.y + distance_to_wall * ray.y;
	else
		wall_hit_coord = player_position_in_cell.x + distance_to_wall * ray.x;
	wall_hit_coord -= floor(wall_hit_coord);
	texture.x = (int)(wall_hit_coord * (double)data->texture->width);
	y_increase_step = 1.0 * (double)data->texture->height / (double)line_height;
	position_on_texture = (start_pixel - HEIGHT / 2 + line_height / 2) * y_increase_step;
	draw_celing(data, start_pixel, find_color(data, 'C'), x);
	draw_floor(data, end_pixel, find_color(data, 'F'), x);
	while (start_pixel < end_pixel)
	{
		position_on_texture += y_increase_step;
		if (side == VERTICAL && ray.x < 0)
			text_num = E;
		else if (side == VERTICAL && ray.x > 0)
			text_num = W;
		else if (side == HORIZONTAL && ray.y < 0)
			text_num = N;
		else if (side == HORIZONTAL && ray.y > 0)
			text_num = S;
		int texY = (int)position_on_texture & (data->texture[text_num].height - 1);
		offset = data->texture[text_num].image.addr + (texY * data->texture[text_num].image.line_length 
			+ texture.x * data->texture[text_num].image.bits_per_pixel / 8);
		color = *(unsigned int *)offset;
		my_mlx_pixel_put(&data->img, x, start_pixel, color);
		start_pixel++;
	}
	// make_it_color(side, data, player_cell, start_pixel, end_pixel, x);
}

void	dda(t_data *data)
{
	t_point			player_position_in_cell;
	double			distance_to_wall;
	t_coordinates	player_cell;
	t_fvector		ray;
	t_fvector		initial_step;
	t_fvector		fixed_step;
	t_coordinates 	step;
	t_side			side;
	int				x;

	x = 0;
	get_player_position_on_map(data, &player_position_in_cell);
	get_player_cell(player_position_in_cell, &player_cell);
	while (x < WIDTH)
	{
		get_x_ray_coordinates(x, data, &ray);
		get_fixed_step_between_lines(ray, &fixed_step);
		get_initial_step(ray, player_position_in_cell, player_cell, &initial_step, fixed_step, &step);
		distance_to_wall = find_distance_to_wall(data, fixed_step, &initial_step, &side, &step, player_cell);
		draw_line_text(data, side, x, ray, player_position_in_cell, /* player_cell,  */distance_to_wall);
		x++;
	}
}
