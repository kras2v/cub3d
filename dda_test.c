/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:28:10 by kvalerii          #+#    #+#             */
/*   Updated: 2025/06/11 15:25:02 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	clear_display(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH * 2)
		{
			my_mlx_pixel_put(&(data->img), x, y, BLACK);
			x++;
		}
		y++;
	}
}

void	draw_player(t_data *data)
{	
	int	x;
	int	y;

	y = 0;
	while (y < PLAYER_SIZE)
	{
		x = 0;
		my_mlx_pixel_put(&(data->img), data->player.position.x + x + WIDTH - 1, data->player.position.y + y, GREEN);
		while (x < PLAYER_SIZE)
		{
			my_mlx_pixel_put(&(data->img), data->player.position.x + x + WIDTH - 1, data->player.position.y + y, GREEN);
			x++;
		}
		y++;
	}
	t_fvector new_point;
	new_point.x = data->player.position.x + PLAYER_SIZE / 2 + data->player.direction.x * 100.0;
	new_point.y = data->player.position.y + PLAYER_SIZE / 2 + data->player.direction.y * 100.0;
	// printf("player: (%f, %f) |  a: (%f, %f) |  dir: (%f, %f)\n", data->player.position.x, data->player.position.y, new_point.x, new_point.y, data->player.direction.x, data->player.direction.y);
	draw_line(data, data->player.position, new_point, WHITE, 1);
}

void	fill_square(t_data *data, int px, int py, t_colors color)
{
	int	x;
	int	y;

	y = 0;
	while (y < CELL_SIZE)
	{
		x = 0;
		while (x < CELL_SIZE)
		{
			my_mlx_pixel_put(&(data->img), x + px, y + py, color);
			x++;
		}
		y++;
	}
}

void	border_square(t_data *data, int px, int py)
{
	int	x;
	int	y;

	y = 0;
	while (y < CELL_SIZE)
	{
		x = 0;
		while (x < CELL_SIZE)
		{
			if ((y == 0 || y == CELL_SIZE - 1)
			|| (x == 0 || x == CELL_SIZE - 1))
			{
				my_mlx_pixel_put(&(data->img), x + px, y + py, PURPLE);
			}
			x++;
		}
		y++;
	}
}

void	rotate(t_fvector *point, double radian)
{
	t_fvector	temp;

	temp.x = point->x;
	temp.y = point->y;
	point->x = (temp.x * cos(radian) - temp.y * sin(radian));
	point->y = (temp.x * sin(radian) + temp.y * cos(radian));
	printf("dir x: %f | y: %f\n", point->x, point->y);
}

bool is_direction(int coordinate)
{
	return (coordinate == NORTH
		|| coordinate == EAST
		|| coordinate == SOUTH
		|| coordinate == WEST);
}

void	draw_map_fill(t_data *data)
{
	int	px;
	int	py;

	py = 0;
	while (py < MAP_HEIGHT)
	{
		px = 0;
		while (px < MAP_WIDTH)
		{
			if (data->map[py][px] >= 1 && !is_direction(data->map[py][px]))
			{
				t_colors color;
				switch(data->map[py][px])
				{
					case 1:  color = RED;  break;
					case 2:  color = GREEN;  break;
					case 3:  color = BLUE;   break;
					case 4:  color = YELLOW;  break;
					default: color = WHITE; break;
				}
				fill_square(data, px * CELL_SIZE + WIDTH - 1, py * CELL_SIZE, color);
				border_square(data,  px * CELL_SIZE + WIDTH - 1, py * CELL_SIZE);
			}
			px++;
		}
		py++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
}

void	draw_map_border(t_data *data)
{
	int	px;
	int	py;

	py = 0;
	while (py < MAP_HEIGHT)
	{
		px = 0;
		while (px < MAP_WIDTH)
		{
			if (data->map[py][px] >= 1 && !is_direction(data->map[py][px]))
			{
				t_colors color;
				switch(data->map[py][px])
				{
					case 1:  color = RED;  break;
					case 2:  color = GREEN;  break;
					case 3:  color = BLUE;   break;
					case 4:  color = YELLOW;  break;
					default: color = WHITE; break;
				}
				fill_square(data, px * CELL_SIZE + WIDTH - 1, py * CELL_SIZE, color);
			}
			border_square(data,  px * CELL_SIZE + WIDTH - 1, py * CELL_SIZE);
			px++;
		}
		py++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
}

void	display(t_data *data)
{
	clear_display(data);
	draw_map_border(data);
	dda(data);
	draw_map_fill(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
}

int	close_event(t_data *data)
{
	if (data && data->mlx)
	{
		if (data->img.ptr)
			mlx_destroy_image(data->mlx, data->img.ptr);
		if (data->mlx_win)
			mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
		free(data);
	}
	exit(0);
	return(0);
}

int	check_wall(t_move move, t_data *data, double px, double py)
{
	int	direction_cell;
	int	cell_left;
	int	cell_right;

	direction_cell = 0;
	if (move == UP || move == DOWN)
	{
		if (move == UP)
			direction_cell = (int)(py / CELL_SIZE);
		else
			direction_cell = (int)((py + PLAYER_SIZE) / CELL_SIZE);

		cell_left = (int)(px / CELL_SIZE);
		cell_right = (int)((px + PLAYER_SIZE) / CELL_SIZE);

		printf("px: %f, py: %f, mapx: %d, mapy: %d, is wall: %d\n", px, py + PLAYER_SIZE, cell_right, direction_cell, data->map[direction_cell][cell_right] > 0);

		if (px >= cell_left * CELL_SIZE && px <= (cell_left + 1) * CELL_SIZE
		&& (px + PLAYER_SIZE) >= cell_left * CELL_SIZE && (px + PLAYER_SIZE) <= (cell_left + 1) * CELL_SIZE)
		{
			return (data->map[direction_cell][cell_left] > 0
				&& !is_direction(data->map[direction_cell][cell_left]));
		}
		else
		{
			return ((data->map[direction_cell][cell_left] > 0
				&& !is_direction(data->map[direction_cell][cell_left]))
				|| (data->map[direction_cell][cell_right] > 0
				&& !is_direction(data->map[direction_cell][cell_right])));
		}
	}
	if (move == RIGHT || move == LEFT)
	{
		if (move == RIGHT)
			direction_cell = (int)((px + PLAYER_SIZE) / CELL_SIZE);
		else
			direction_cell = (int)(px / CELL_SIZE);

		cell_left = (int)(py / CELL_SIZE);
		cell_right = (int)((py + PLAYER_SIZE) / CELL_SIZE);

		if (py >= cell_left * CELL_SIZE && py <= (cell_left + 1) * CELL_SIZE
		&& (py + PLAYER_SIZE) >= cell_left * CELL_SIZE && (py + PLAYER_SIZE) <= (cell_left + 1) * CELL_SIZE)
		{
			return (data->map[cell_left][direction_cell] > 0
				&& !is_direction(data->map[cell_left][direction_cell]));
		}
		else
		{
			return ((data->map[cell_left][direction_cell] > 0
				&& !is_direction(data->map[cell_left][direction_cell]))
				|| (data->map[cell_right][direction_cell] > 0
				&& !is_direction(data->map[cell_right][direction_cell])));
		}
	}
	return (0);
}

// bool	is_corner_crossing_border(t_move move, t_data *data, int px, int py)
// {
// 	int	shift_x;
// 	int	shift_y;

// 	shift_y = 0;
// 	while (shift_y < PLAYER_SIZE)
// 	{
// 		shift_x = 0;
// 		while (shift_x < PLAYER_SIZE)
// 		{
// 			if (move == UP && shift_y == 0 && (shift_x == 0 || shift_x == PLAYER_SIZE - 1))
// 			{
// 				if (check_wall(move, data, px + shift_x, py + shift_y) > 0)
// 					return (true);
// 			}
// 			shift_x += PLAYER_SIZE;
// 		}
// 		shift_y += PLAYER_SIZE;
// 	}
// 	return (false);
// }

int	move_player(int keycode, t_data *data)
{
	static struct timeval	old_time;
	static struct timeval	now_time;
	double					frame_time;
	double					move_speed;
	double					rot_speed;
	double					shift_x;
	double					shift_y;
	bool					is_wall;

	if (now_time.tv_sec == 0)
	{
		gettimeofday(&now_time, 0);
	}
	old_time = now_time;
	gettimeofday(&now_time, 0);
	frame_time = (now_time.tv_sec - old_time.tv_sec) + (now_time.tv_usec - old_time.tv_usec) / 1000000.0;
	if (frame_time > 0.1)
		printf("FPS %f\n", 1.0 / frame_time);
	if (frame_time > 0.2)
		frame_time = 0.2;
	clear_display(data);
	dda(data);

	move_speed = frame_time * 25.0;
	rot_speed = frame_time;

	shift_x = 0;
	shift_y = 0;
	is_wall = false;
	if (keycode == XK_W || keycode == XK_w)
	{
		shift_x += data->player.direction.x * move_speed;
		shift_y += data->player.direction.y * move_speed;
		if (data->player.direction.y < 0)
			is_wall = check_wall(UP, data, data->player.position.x + shift_x, data->player.position.y + shift_y);
		else
			is_wall = check_wall(DOWN, data, data->player.position.x + shift_x, data->player.position.y + shift_y);
	}
	if (keycode == XK_S || keycode == XK_s)
	{
		shift_x -= data->player.direction.x * move_speed;
		shift_y -= data->player.direction.y * move_speed;
			if (data->player.direction.y > 0)
			is_wall = check_wall(UP, data, data->player.position.x + shift_x, data->player.position.y + shift_y);
		else
			is_wall = check_wall(DOWN, data, data->player.position.x + shift_x, data->player.position.y + shift_y);
	}
	if (keycode == XK_A || keycode == XK_a)
	{
		shift_x += data->player.direction.y * move_speed;
		shift_y += -data->player.direction.x * move_speed;
		if (data->player.direction.y < 0)
			is_wall = check_wall(LEFT, data, data->player.position.x + shift_x, data->player.position.y + shift_y);
		else
			is_wall = check_wall(RIGHT, data, data->player.position.x + shift_x, data->player.position.y + shift_y);
	}
	if (keycode == XK_D || keycode == XK_d)
	{
		shift_x += -data->player.direction.y * move_speed;
		shift_y += data->player.direction.x * move_speed;
		if (data->player.direction.y > 0)
			is_wall = check_wall(LEFT, data, data->player.position.x + shift_x, data->player.position.y + shift_y);
		else
			is_wall = check_wall(RIGHT, data, data->player.position.x + shift_x, data->player.position.y + shift_y);
	}

	if (is_wall == false)
	{
		data->player.position.x += shift_x;
		data->player.position.y += shift_y;
	}

	if (keycode == XK_Left)
	{
		rotate(&(data->player.direction), -rot_speed);
	}
	else if (keycode == XK_Right)
	{
		rotate(&(data->player.direction), rot_speed);
	}
	return (0);
}

int	key_press_event(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		close_event(data);
	}
	if ((keycode == XK_W || keycode == XK_w)
		|| (keycode == XK_S || keycode == XK_s)
		|| (keycode == XK_D || keycode == XK_d)
		|| (keycode == XK_A || keycode == XK_a )
		|| (keycode == XK_Right || keycode == XK_Left))
	{
		move_player(keycode, data);
		display(data);
	}
	return (0);
}


int print_coords(int button, int x, int y, t_data *param)
{
	(void)param;
	(void)button;
	printf("px: %d | py: %d | map_x: %d | map_y: %d | is_wall: %d|\n", x - WIDTH, y, ( x - WIDTH) / CELL_SIZE, y / CELL_SIZE, param->map[y / CELL_SIZE][(x - WIDTH) / CELL_SIZE] > 0
		&& !is_direction(param->map[y / CELL_SIZE][(x - WIDTH) / CELL_SIZE]));
	return (0);
}

void	init_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, ON_DESTROY, NO_EVENT_MASK, close_event, data);
	mlx_mouse_hook(data->mlx_win, print_coords, data);
	mlx_hook(data->mlx_win, ON_KEYDOWN, KEY_PRESS_MASK, key_press_event, data);
}

void	init_player2(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			if (data->map[y][x] == 'N')
			{
				data->player.direction.x = 0;
				data->player.direction.y = -1;
				data->player.position.x = x * CELL_SIZE + CELL_SIZE / 4;
				data->player.position.y = y * CELL_SIZE + CELL_SIZE / 4;
			}
			else if (data->map[y][x] == 'E')
			{
				data->player.direction.x = 1;
				data->player.direction.y = 0;
				data->player.position.x = x * CELL_SIZE + CELL_SIZE / 4;
				data->player.position.y = y * CELL_SIZE + CELL_SIZE / 4;
			}
			else if (data->map[y][x] == 'S')
			{
				data->player.direction.x = 0;
				data->player.direction.y = 1;
				data->player.position.x = x * CELL_SIZE + CELL_SIZE / 4;
				data->player.position.y = y * CELL_SIZE + CELL_SIZE / 4;
			}
			else if (data->map[y][x] == 'W')
			{
				data->player.direction.x = -1;
				data->player.direction.y = 0;
				data->player.position.x = x * CELL_SIZE + CELL_SIZE / 4;
				data->player.position.y = y * CELL_SIZE + CELL_SIZE / 4;
			}
			x++;
		}
		y++;
	}
	data->player.rotation_angle = 0;
}


void	init_player(t_data *data)
{
	data->player.position.x = WIDTH / 2;
	data->player.position.y = HEIGHT / 2;
	data->player.rotation_angle = 0;
	data->player.direction.x = 1;
	data->player.direction.y = 0;
}

void	free_map(int **map, int i)
{
	int j;

	j = 0;
	while (j < i)
	{
		free(map[j]);
		j++;
	}
	free(map);
}

void	print_map(int **map)
{
	int i;
	int j;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			printf("%d ", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(void)
{
	t_data	*data;

	int worldMap[MAP_WIDTH][MAP_HEIGHT]=
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,'N',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIDTH * 2, HEIGHT, "cub3d");
	data->img.ptr = mlx_new_image(data->mlx, WIDTH * 2, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	data->map = malloc(sizeof(int *) * MAP_HEIGHT);
	if (data->map == NULL)
	{
		close_event(data);
	}
	int i = 0;
	while (i < MAP_HEIGHT)
	{
		data->map[i] = malloc(sizeof(int) * MAP_WIDTH);
		if (data->map[i] == NULL)
		{
			free_map(data->map, i);
		}
		int j = 0;
		while (j < MAP_WIDTH)
		{
			data->map[i][j] = worldMap[i][j];
			j++;
		}
		i++;
	}
	// print_map(data->map);
	init_player2(data);
	dda(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
	display(data);
	init_hooks(data);
	mlx_loop(data->mlx);
	return (0);
}