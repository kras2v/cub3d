/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_init_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:58:24 by valeriia          #+#    #+#             */
/*   Updated: 2025/08/01 18:08:45 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void	textures_init(t_data *data, char *line, char c)
{
	while (*line && *line == ' ')
		line++;
	line += 2;
	while (*line && *line != '.')
	{
		if (*line != ' ')
			return ;
		line++;
	}
	if (c == 'N' && !data->texture_names[N])
		data->texture_names[N] = ft_strdup(line);
	else if (c == 'E' && !data->texture_names[E])
		data->texture_names[E] = ft_strdup(line);
	else if (c == 'W' && !data->texture_names[W])
		data->texture_names[W] = ft_strdup(line);
	else if (c == 'S' && !data->texture_names[S])
		data->texture_names[S] = ft_strdup(line);
	else
	{
		printf("Double textures\n");
		close_event(data);
	}
}

void	colors_init(t_data *data, char *line, char c)
{
	char	*p_line;

	p_line = line;
	while (*p_line && *p_line == ' ')
	{
		p_line++;
	}
	p_line += 1;
	while (*p_line && *p_line == ' ')
	{
		p_line++;
	}
	if (c == 'F' && data->f == -1)
	{
		data->f = find_color(data, p_line);
	}
	else if (c == 'C' && data->c == -1)
	{
		data->c = find_color(data, p_line);
	}
	else
	{
		printf("Double textures\n");
		close_event(data);
	}
}

void	assign_map_params(t_data *data)
{
	int	y;
	int	width;
	int	height;

	y = 0;
	height = 0;
	while (data->map[y] != NULL)
	{
		if (ft_strchr(data->map[y], WALL) || ft_strchr(data->map[y], EMPTY))
		{
			width = ft_strlen(data->map[y]);
			if (data->map_width < width)
				data->map_width = width;
			height++;
		}
		y++;
	}
	data->map_height = height;
}

void	map_init(
	t_data *data,
	int y
)
{
	data->map = &data->script[y];
	assign_map_params(data);
	replace_null_terminated_strings(data, data->map);
}

bool	is_script_valid(t_data *data)
{
	int	y;

	y = 0;
	while (data->script[y] && !data->map)
	{
		if (!ft_strncmp(data->script[y], "NO", 2))
			textures_init(data, data->script[y], 'N');
		else if (!ft_strncmp(data->script[y], "EA", 2))
			textures_init(data, data->script[y], 'E');
		else if (!ft_strncmp(data->script[y], "WE", 2))
			textures_init(data, data->script[y], 'W');
		else if (!ft_strncmp(data->script[y], "SO", 2))
			textures_init(data, data->script[y], 'S');
		else if (!ft_strncmp(data->script[y], "F", 1))
			colors_init(data, data->script[y], 'F');
		else if (!ft_strncmp(data->script[y], "C", 1))
			colors_init(data, data->script[y], 'C');
		else if (is_map_line(data->script[y]))
			map_init(data, y);
		else if ((ft_strncmp(data->script[y], "\n", 1)))
			return (close_on_error(data,
					"Error with .cub file format\n"), false);
		y++;
	}
	return (true);
}
