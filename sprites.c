# include "dda.h"

long int	time_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	init_sprite(t_data *data)
{
	data->sprite = ft_calloc(1, sizeof(t_sprite));
	data->sprite->texture[0] = mlx_xpm_file_to_image(data->mlx, "./walls/xpm/ducky-idle1.xpm", &(int){48}, &(int){48});
	data->sprite->texture[1] = mlx_xpm_file_to_image(data->mlx, "./walls/xpm/ducky-idle2.xpm", &(int){48}, &(int){48});
	if (!data->sprite || !data->sprite->texture[1] || !data->sprite->texture[0])
	{
		printf("Failed to load ducky.xpm or !calloc\n");
		close_event(data);
	}
	data->sprite->current_frame = 0;
	data->sprite->frame_timer = 0.0;
	data->sprite->frame_delay = 200;
}

void	find_sprite_pos(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < data->map_height)
	{
		while (j < data->map_width)
		{
			j = 0;
			if (data->map[i][j] == '2')
			{
				data->sprite->x = j + 0.5;
				data->sprite->y = i + 0.5;
				data->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}
void	update_sprite(t_data *data)
{
	long int now = time_now();
	if (now - data->sprite->frame_timer >= data->sprite->frame_delay)
	{
		data->sprite->current_frame++;
		if (data->sprite->current_frame >= 2)
			data->sprite->current_frame = 0;
		data->sprite->frame_timer = now;
    }
}