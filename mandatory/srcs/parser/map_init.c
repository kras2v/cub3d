/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:50:49 by kvalerii          #+#    #+#             */
/*   Updated: 2025/08/03 12:12:37 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include <unistd.h>
#include <fcntl.h>

void	free_double_arr(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

bool	is_file_name_valid(
	t_data *data,
	char *name
)
{
	char	*find;

	find = ft_strrchr(name, '.');
	if (find == name || !find)
		return (close_on_error(data, FILE_NAME_ERR), false);
	if (ft_strncmp(find, ".cub", ft_strlen(name)) != 0)
		return (close_on_error(data, FILE_NAME_ERR), false);
	return (true);
}

char	*read_map_str(int fd)
{
	char	*temp;
	char	*map_str;
	char	*new_map_str;

	map_str = ft_strdup("");
	if (!map_str)
		return (NULL);
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		new_map_str = ft_strjoin(map_str, temp);
		free(map_str);
		free(temp);
		if (!new_map_str)
			return (NULL);
		map_str = new_map_str;
	}
	return (map_str);
}

char	**read_map(
	t_data *data,
	char *map_script
)
{
	int		fd;
	char	*map_str;
	char	**map_array;

	fd = open(map_script, O_RDONLY);
	if (fd == -1)
		return (close_on_error(data, NULL), NULL);
	map_str = read_map_str(fd);
	close(fd);
	if (!map_str)
		return (close_on_error(data, NULL), NULL);
	map_array = ft_split(map_str, '\n');
	free(map_str);
	if (!map_array)
		return (close_on_error(data, NULL), NULL);
	return (map_array);
}

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


void	read_actual_map(
	t_data *data,
	char *map_script
)
{
	int		fd;
	char	*line;
	int		total_counter;

	total_counter = 0;
	fd = open(map_script, O_RDONLY);
	if (fd == -1)
		close_on_error(data, NULL);
	count_lines(data, fd);
	fd = open(map_script, O_RDONLY);
	if (fd == -1)
		close_on_error(data, NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (total_counter < data->map_start_line)
		{
			total_counter++;
			free(line);
			continue ;
		}
		if (*line == '\n')
		{
			free(line);
			close(fd);
			while (1)
			{
				line = get_next_line(fd);
				if (!line)
					break ;
				free(line);
			}
			close_on_error(data, "New line in map\n");
		}
		free(line);
		total_counter++;
	}
	close(fd);
}
