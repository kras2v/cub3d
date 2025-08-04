/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_init_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:58:24 by valeriia          #+#    #+#             */
/*   Updated: 2025/08/04 17:10:23 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void	textures_init(t_data *data, char *line, char c)
{
	char	*dline;

	line += 2;
	while (*line && *line == ' ')
		line++;
	dline = ft_strdup(line);
	if (!dline)
		close_on_error(data, "Malloc fail\n");
	if (c == 'N' && !data->texture_names[N])
		data->texture_names[N] = dline;
	else if (c == 'E' && !data->texture_names[E])
		data->texture_names[E] = dline;
	else if (c == 'W' && !data->texture_names[W])
		data->texture_names[W] = dline;
	else if (c == 'S' && !data->texture_names[S])
		data->texture_names[S] = dline;
	else
	{
		free(dline);
		close_on_error(data, "Double textures\n");
		close_event(data);
	}
}

void	colors_init(t_data *data, char *line, char c)
{
	char	*p_line;

	p_line = line;
	p_line += 1;
	while (*p_line && *p_line == ' ')
	{
		p_line++;
	}
	if (!(*p_line >= '0' && *p_line <= '9'))
		close_on_error(data, "Wrong input\n");
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
		close_on_error(data, "Double colors\n");
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
