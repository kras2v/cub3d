/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:50:49 by kvalerii          #+#    #+#             */
/*   Updated: 2025/08/01 18:23:58 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_bonus.h"
#include <unistd.h>
#include <fcntl.h>

void	free_double_arr(char **map)
{
	int	i;

	i = 0;
	if (!map || !*map)
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
