/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_n_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:22:17 by eklymova          #+#    #+#             */
/*   Updated: 2025/08/06 16:37:58 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include <unistd.h>
#include <fcntl.h>

bool	is_map_line_valid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1')
			return (line[i] == '\n' && !line[i + 1] && i > 0);
		i++;
	}
	return (true);
}

void	count_lines(t_data *data, int fd)
{
	int		count;
	char	*line;
	bool	start_count;
	int		total_counter;

	total_counter = 0;
	start_count = 0;
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!start_count && is_map_line_valid(line))
		{
			data->map_start_line = total_counter;
			start_count = 1;
		}
		if (start_count)
			count++;
		total_counter++;
		free(line);
	}
	close (fd);
}

static void	skip_to_map_start(t_data *data, int fd, int *counter)
{
	char	*line;

	while (*counter < data->map_start_line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		(*counter)++;
	}
}

void	read_actual_map_lines(t_data *data, int fd, int start_line, char *line)
{
	int		counter;

	counter = start_line;
	skip_to_map_start(data, fd, &counter);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line == '\n')
		{
			free(line);
			while (1)
			{
				line = get_next_line(fd);
				if (!line)
					break ;
				free(line);
			}
			close(fd);
			close_on_error(data, "New line in map\n");
		}
		free(line);
		counter++;
	}
}

void	read_actual_map(t_data *data, char *map_script)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(map_script, O_RDONLY);
	if (fd == -1)
		close_on_error(data, NULL);
	count_lines(data, fd);
	close(fd);
	fd = open(map_script, O_RDONLY);
	if (fd == -1)
		close_on_error(data, NULL);
	read_actual_map_lines(data, fd, 0, line);
	close(fd);
}
