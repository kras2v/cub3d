/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:03:35 by valeriia          #+#    #+#             */
/*   Updated: 2025/06/23 14:54:31 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	swap_points(t_fvector *a, t_fvector *b)
{
	t_fvector temp;

	temp.x = a->x;
	temp.y = a->y;
	a->x = b->x;
	a->y = b->y;

	b->x = temp.x;
	b->y = temp.y;
}

void	get_player_position_on_map(
	t_data *data,
	t_point *player_position_in_cell)
{
	player_position_in_cell->x = (data->player.position.x / CELL_SIZE);
	player_position_in_cell->y = (data->player.position.y / CELL_SIZE);
}

void	get_player_cell(
	t_point player_position_in_cell,
	t_coordinates *player_cell)
{
	player_cell->x = (int)player_position_in_cell.x;
	player_cell->y = (int)player_position_in_cell.y;
}

void	get_initial_step(
	t_data *data,
	t_fvector ray,
	t_point player_position_in_cell,
	t_coordinates player_cell,
	t_fvector *initial_step,
	t_fvector fixed_step,
	int *step
	)
{
	if (ray.x < 0)
	{
		*step = -1;
		initial_step->x = (player_position_in_cell.x - player_cell.x) * fixed_step.x;
	}
	else
	{
		*step = 1;
		initial_step->x = (player_position_in_cell.x + 1.0 - player_cell.x) * fixed_step.x;
	}
	if (ray.y < 0)
	{
		*step = -1;
		initial_step->y = (player_position_in_cell.y - player_cell.y) * fixed_step.y;
	}
	else
	{
		*step = 1;
		initial_step->y = (player_position_in_cell.y + 1.0 - player_cell.y) * fixed_step.y;
	}
}

void	get_fixed_step_between_lines(
	t_data *data,
	t_fvector ray,
	t_fvector *fixed_step
	)
{
	fixed_step->x = INFINITY;
	fixed_step->y = INFINITY;
	if (fixed_step->x != 0)
	{
		fixed_step->x = abs(1 / ray.x);
	}
	if (fixed_step->y != 0)
	{
		fixed_step->y = abs(1 / ray.y);
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

void	find_wall_hit(
	t_fvector *fixed_step,
	t_fvector *initial_step,
	t_side side,
	)
{

}

void	dda_revision(t_data *data)
{
	t_point			player_position_in_cell;
	t_coordinates	player_cell;
	t_fvector		ray;
	t_fvector		initial_step;
	t_fvector		fixed_step;
	int				step;
	int				x;

	x = 0;
	while (x < WIDTH)
	{
		get_player_cell(player_position_in_cell, &player_cell);
		get_player_position_on_map(data, &player_position_in_cell);
		get_x_ray_coordinates(x, data, &ray);
		get_fixed_step_between_lines(data, ray, &fixed_step);
		get_initial_step(data, ray, player_position_in_cell, player_cell, &initial_step, fixed_step, &step);

		x++;
	}
	
}

void	dda(t_data *data)
{
	double	pos_pl_x; //
	double	pos_pl_y; //
	double	map_x; //
	double	map_y; //
	double	camera_x; //
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	t_side	side;
	double	perp_wall_dist;
	int		line_height;

	int		x;

	x = 0;
	side = VERTICAL;
	double theta_player = atan2(data->player.direction.y, data->player.direction.x);
	double cos_theta_ray;
	double sin_theta_ray;
	double theta_ray;

	double sin_cos[2][WIDTH];

	x = 0;
	while (x < WIDTH)
	{
		hit = 0;

		pos_pl_x = (data->player.position.x / CELL_SIZE);
		pos_pl_y = (data->player.position.y / CELL_SIZE);

		map_x = floor(pos_pl_x);
		map_y = floor(pos_pl_y);

		cos_theta_ray = sin_cos[1][x];
		sin_theta_ray = sin_cos[0][x];

		delta_dist_x = fabs(1.0 / cos_theta_ray);
		delta_dist_y = fabs(1.0 / sin_theta_ray);



		if (sin_theta_ray < 0.0)
		{
			step_y = -1;
			side_dist_y = (pos_pl_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (1.0 + map_y - pos_pl_y) * delta_dist_y;
		}

		while (hit == 0.0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = VERTICAL;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = HORIZONTAL;
			}
			if (data->map[(int)map_y][(int)map_x] > 0 && !is_direction(data->map[(int)map_y][(int)map_x]))
				hit = 1;
		}
		if (side == VERTICAL)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);

		t_fvector	new_point;
		new_point.x = map_x * CELL_SIZE;
		new_point.y = map_y * CELL_SIZE;
		draw_line(data, data->player.position, new_point, 0xFFFFFF, 1);

		double corrected_dist = perp_wall_dist /* cos(theta_ray - theta_player) */;
		line_height = HEIGHT / corrected_dist;

		// t_fvector	first;
		// t_fvector	second;

		// first.x = x;
		// second.x = x;
		// first.y = start;
		// second.y = end;

		// t_colors color;
		// switch(data->map[map_y][map_x])
		// {
		// 	case 1:  color = RED;  break; //red
		// 	case 2:  color = GREEN;  break; //green
		// 	case 3:  color = BLUE;   break; //blue
		// 	case 4:  color = YELLOW;  break; //white
		// 	default: color = WHITE; break; //yellow
		// }

		// if (side == 1)
		// 	color = color / 1.5;
		// // draw_line(data, first, second, color, 0);
		// while (first.y < second.y)
		// { 
		// 	put_image(data, first.x, first.y);
		// 	first.y += data->texture->height;
		// 	// printf("%f - %f\n", first.y, second.y);
		// }

		// int		tex_num = data->map[map_x][map_y] - 1; //1 subtracted from it so that texture 0 can be used!
		double	wall; //where exactly the wall was hit
		if (side == VERTICAL)
		{
			wall = pos_pl_x + perp_wall_dist * cos_theta_ray;
		}
		else
		{
			wall = pos_pl_y + perp_wall_dist * sin_theta_ray;
		}
		wall -= floor(wall);
		int	tex_x = (int)(wall * (double)(data->texture->width)); //the pixel column (texX) of the texture you should draw.
		//So you flip the texture column horizontally if the ray hits the wall from the opposite direction.
		if ((side == VERTICAL && cos_theta_ray > 0) || (side == HORIZONTAL && sin_theta_ray < 0))
		{
			tex_x = data->texture->width - tex_x - 1;
		}
		double step = 1.0 * (double)data->texture->height / line_height;
		int start =  HEIGHT / 2 - line_height / 2;
		if (start < 0)
			start = 0;
		int end =  HEIGHT / 2 + line_height / 2;
		if (end >= HEIGHT)
		end = HEIGHT - 1;
		// This centers the texture vertically on the wall slice.
		double tex_pos = (start - HEIGHT / 2 + line_height / 2) * step;
		int	y = start;
		t_texture *texture;
		texture = malloc(sizeof(t_texture));
		texture->image.bits_per_pixel = 0;
		texture->image.line_length = 0;
		texture->image.addr = 0;
		while (y < end)
		{
			//This helps prevent texture coordinate overflow (going out of bounds) by effectively performing a modulo operation, but it's faster because it's just a bitwise AND.
			int tex_y = (int)tex_pos & (data->texture->height - 1);
			tex_pos += step;
			if (side == VERTICAL && cos_theta_ray > 0)
				texture = &data->texture[1];
			else if (side == VERTICAL && cos_theta_ray <= 0)
				texture = &data->texture[3];
			if (side == HORIZONTAL && sin_theta_ray > 0)
				texture = &data->texture[0];
			else if (side == HORIZONTAL && sin_theta_ray <= 0)
				texture = &data->texture[2];
			char *offset = texture->image.addr + (tex_y * texture->image.line_length + x * texture->image.bits_per_pixel / 8);
			int color = *(unsigned int *)offset;
			// if (y == start)
			// 	printf("color %d and texture %s\n", color, data->texture->name);
			my_mlx_pixel_put(&data->img, x, y, color);
			y++;
		}
		x++;
	}
}

void	draw_horizontal(t_data *data, t_fvector a, t_fvector b, t_colors color, int second_window)
{
	int	dx;
	int	dy;
	int	p;
	int	y;
	int	x;
	int	dir;

	if (a.x > b.x)
	{
		swap_points(&a, &b);
	}
	dx = b.x - a.x;
	dy = b.y - a.y;
	if (dy < 0)
	{
		dir = -1;
	}
	else
	{
		dir = 1;
	}
	dy *= dir;
	if (dx != 0)
	{
		x = 0;
		y = a.y;
		p = 2 * dy - dx;
		while (x < dx + 1)
		{
			if (a.x + x >= 0 && a.x + x < WIDTH && y >= 0 && y < HEIGHT)
				my_mlx_pixel_put(&(data->img), a.x + x + second_window * WIDTH, y, color);
			if (p >= 0)
			{
				y += dir;
				p = p - 2 * dx;
			}
			p = p + 2 * dy;
			x++;
		}
	}
}

void	draw_vertical(t_data *data, t_fvector a, t_fvector b, t_colors color, int second_window)
{
	int	dx;
	int	dy;
	int	p;
	int	y;
	int	x;
	int	dir;

	if (a.y > b.y)
	{
		swap_points(&a, &b);
	}
	dx = b.x - a.x;
	dy = b.y - a.y;
	if (dx < 0)
	{
		dir = -1;
	}
	else
	{
		dir = 1;
	}
	dx *= dir;
	if (dy != 0)
	{
		y = 0;
		x = a.x;
		p = 2 * dx - dy;
		while (y < dy + 1)
		{
			if (y + a.y >= 0 && y + a.y < HEIGHT && x >= 0 && x < WIDTH)
				my_mlx_pixel_put(&(data->img), x + second_window * WIDTH, y + a.y, color);
			if (p >= 0)
			{
				x += dir;
				p = p - 2 * dy;
			}
			p = p + 2 * dx;
			y++;
		}
	}
}

void	draw_line(t_data *data, t_fvector a, t_fvector b, t_colors color, int second_window)
{
	a.x += PLAYER_SIZE / 2;
	a.y += PLAYER_SIZE / 2;
	if (fabs(b.x - a.x) >= fabs(b.y - a.y))
	{
		draw_horizontal(data, a, b, color, second_window);
	}
	else
	{
		draw_vertical(data, a, b, color, second_window);
	}
}

#include <errno.h>
#include <string.h>
#include <string.h>
#include <unistd.h>

void	put_image(t_data *data, t_texture *texture, int x, int y)
{
	(void)y;
	if (mlx_put_image_to_window(data->mlx, data->mlx_win, texture->image.ptr, x * texture->width, y))
	{
		printf("NO PUT IMAGE %s\n", strerror(errno));
	}
}
