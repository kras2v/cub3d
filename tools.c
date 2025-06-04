/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:03:35 by valeriia          #+#    #+#             */
/*   Updated: 2025/06/04 11:22:43 by valeriia         ###   ########.fr       */
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


void	dda(t_data *data)
{
	int		map_x;
	int		map_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;

	int		x;
	x = 0;
	side = 0;
	double theta_player = atan2(data->player.direction.y, data->player.direction.x);
	double theta_ray;
	while (x < WIDTH)
	{
		hit = 0;
		camera_x = 2.0 * (double)x / (double)WIDTH - 1.0;
		theta_ray = theta_player + camera_x * PI / 6;

		map_x = (int)data->player.position.x / CELL_SIZE;
		map_y = (int)data->player.position.y / CELL_SIZE;

		double cos_theta_ray = sec(theta_ray);
		if (ray_dir_x == 0)
			delta_dist_x = 1e30;
		else
			delta_dist_x = fabs(1 / ray_dir_x);

		if (ray_dir_y == 0)
			delta_dist_y = 1e30;
		else
			delta_dist_y = fabs(1 / ray_dir_y);

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->player.position.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->player.position.x) * delta_dist_x;
		}

		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->player.position.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (1.0 + map_y - data->player.position.y) * delta_dist_y;
		}

		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (data->map[map_y][map_x] > 0)
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);
		
		line_height = HEIGHT / perp_wall_dist;
		int start =  HEIGHT / 2 - line_height / 2;
		if (start < 0)
			start = 0;
		int end =  HEIGHT / 2 + line_height / 2;
		if (end >= HEIGHT)
			end = HEIGHT - 1;
		
		t_fvector	first;
		t_fvector	second;

		first.x = x;
		second.x = x;
		first.y = start;
		second.y = end;

		t_colors color;
		switch(data->map[map_x][map_y])
		{
			case 1:  color = RED;  break; //red
			case 2:  color = GREEN;  break; //green
			case 3:  color = BLUE;   break; //blue
			case 4:  color = WHITE;  break; //white
			default: color = YELLOW; break; //yellow
		}

		if (side == 1)
			color = color / 2;
		draw_line(data, first, second, color, 0);
		x++;
	}
}


// void	dda(t_data *data)
// {
// 	int		map_x;
// 	int		map_y;
// 	double	camera_x;
// 	double	ray_dir_x;
// 	double	ray_dir_y;
// 	double	side_dist_x;
// 	double	side_dist_y;
// 	double	delta_dist_x;
// 	double	delta_dist_y;
// 	int		step_x;
// 	int		step_y;
// 	int		hit;
// 	int		side;
// 	double	perp_wall_dist;
// 	int		line_height;

// 	int		x;
// 	x = 0;
// 	side = 0;
// 	while (x < WIDTH)
// 	{
// 		hit = 0;
// 		camera_x = 2.0 * (double)x / (double)WIDTH - 1.0;
// 		ray_dir_x = data->player.direction.x + data->player.plane.x * camera_x;
// 		ray_dir_y = data->player.direction.y + data->player.plane.y * camera_x;

// 		map_x = (int)data->player.position.x / CELL_SIZE;
// 		map_y = (int)data->player.position.y / CELL_SIZE;
// 		printf("POS: x = %f  y = %f\n", data->player.position.x, data->player.position.y);

		
// 		if (ray_dir_x == 0)
// 			delta_dist_x = 1e30;
// 		else
// 			delta_dist_x = fabs(1 / ray_dir_x);

// 		if (ray_dir_y == 0)
// 			delta_dist_y = 1e30;
// 		else
// 			delta_dist_y = fabs(1 / ray_dir_y);

// 		if (ray_dir_x < 0)
// 		{
// 			step_x = -1;
// 			side_dist_x = (data->player.position.x - map_x) * delta_dist_x;
// 		}
// 		else
// 		{
// 			step_x = 1;
// 			side_dist_x = (map_x + 1.0 - data->player.position.x) * delta_dist_x;
// 		}

// 		if (ray_dir_y < 0)
// 		{
// 			step_y = -1;
// 			side_dist_y = (data->player.position.y - map_y) * delta_dist_y;
// 		}
// 		else
// 		{
// 			step_y = 1;
// 			side_dist_y = (1.0 + map_y - data->player.position.y) * delta_dist_y;
// 		}

// 		while (hit == 0)
// 		{
// 			if (side_dist_x < side_dist_y)
// 			{
// 				side_dist_x += delta_dist_x;
// 				map_x += step_x;
// 				side = 0;
// 			}
// 			else
// 			{
// 				side_dist_y += delta_dist_y;
// 				map_y += step_y;
// 				side = 1;
// 			}
// 			if (data->map[map_y][map_x] > 0)
// 				hit = 1;
// 		}
// 		if (side == 0)
// 			perp_wall_dist = (side_dist_x - delta_dist_x);
// 		else
// 			perp_wall_dist = (side_dist_y - delta_dist_y);
		
// 		line_height = HEIGHT / perp_wall_dist;
// 		int start =  HEIGHT / 2 - line_height / 2;
// 		if (start < 0)
// 			start = 0;
// 		int end =  HEIGHT / 2 + line_height / 2;
// 		if (end >= HEIGHT)
// 			end = HEIGHT - 1;
		
// 		t_fvector	first;
// 		t_fvector	second;

// 		first.x = x;
// 		second.x = x;
// 		first.y = start;
// 		second.y = end;

// 		t_colors color;
// 		switch(data->map[map_x][map_y])
// 		{
// 			case 1:  color = RED;  break; //red
// 			case 2:  color = GREEN;  break; //green
// 			case 3:  color = BLUE;   break; //blue
// 			case 4:  color = WHITE;  break; //white
// 			default: color = YELLOW; break; //yellow
// 		}

// 		if (side == 1)
// 			color = color / 2;
// 		draw_line(data, first, second, color, 0);
// 		x++;
// 	}
// }

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

t_fvector sum_points(t_fvector a, t_fvector b)
{
	t_fvector	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	return (sum);
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