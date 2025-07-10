#include "dda.h"
#include <unistd.h>
#include <fcntl.h>

void	textures_init(t_data *data, char *line, char c)
{
	while (*line && *line != '.')
		line++;

	if (c == 'N')
		data->N_T = ft_strdup(line);
	else if (c == 'E')
		data->E_T = ft_strdup(line);
	else if (c == 'W')
		data->W_T = ft_strdup(line);
	else if (c == 'S')
		data->S_T = ft_strdup(line);
	else if (c == 'F')
		data->F = ft_strdup(line);
	else if (c == 'C')
		data->C = ft_strdup(line);
}

bool	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1')
			return (false);
		i++;
	}
	return (true);
}

bool	script_init(t_data *data)
{
	int	y;

	y = 0;
	while (data->script[y])
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
			textures_init(data, data->script[y], 'F');
		else if (!ft_strncmp(data->script[y], "C", 1))
			textures_init(data, data->script[y], 'C');
		else if (is_map_line(data->script[y]))
		{
			data->map = &data->script[y];
			break ;
		}
		y++;
	}
	return (true);
}
