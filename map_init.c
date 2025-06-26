#include "dda.h"
#include <unistd.h>
#include <fcntl.h>

void	free_map_init(char **map)
{
	int	i;

	i = 0;
	if (!map || !*map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	valid_input(char *name)
{
	char	*find;

	find = ft_strrchr(name, '.');
	if (find == name || !find)
		return (0);
	if (ft_strncmp(find, ".cub", ft_strlen(name)) != 0)
		return (0);
	return (1);
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
		if (temp[0] == '\n')
			return (free(temp), free(map_str), NULL);
		new_map_str = ft_strjoin(map_str, temp);
		free(map_str);
		free(temp);
		if (!new_map_str)
			return (NULL);
		map_str = new_map_str;
	}
	return (map_str);
}

char	**read_map(char *map_script)
{
	int		fd;
	char	*map_str;
	char	**map_array;

	fd = open(map_script, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map_str = read_map_str(fd);
	close(fd);
	if (!map_str)
		return (NULL);
	map_array = ft_split(map_str, '\n');
	free(map_str);
	if (!map_array)
		return (NULL);
	return (map_array);
}
