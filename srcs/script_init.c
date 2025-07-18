#include "dda.h"
#include <unistd.h>
#include <fcntl.h>

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
	if (c == 'N' && !data->N_T)
		data->N_T = ft_strdup(line);
	else if (c == 'E' && !data->E_T)
		data->E_T = ft_strdup(line);
	else if (c == 'W' && !data->W_T)
		data->W_T = ft_strdup(line);
	else if (c == 'S' && !data->S_T)
		data->S_T = ft_strdup(line);
	else
	{
		printf("Double textures\n");
		close_event(data);
	}
}

void	colors_init(t_data *data, char *line, char c)
{
	while (*line && *line == ' ')
		line++;
	line += 1;
	while (*line && *line == ' ')
		line++;
	if (c == 'F' && !data->F)
		data->F = ft_strdup(line);
	else if (c == 'C' && !data->C)
		data->C = ft_strdup(line);
	else
	{
		printf("Double collors\n");
		close_event(data);
	}
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

void	assign_map_params(t_data *data)
{
	int	y;
	size_t	width;
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

static char	*ft_join(char *res, char *s)
{
	while (*s != '\0')
		*res++ = *s++;
	return (res);
}

char	*ft_strappend(char *s1, char *s2)
{
	char	*res;
	char	*p_res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	res = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	p_res = res;
	p_res = ft_join(p_res, s1);
	p_res = ft_join(p_res, s2);
	*p_res = '\0';
	free(s1);
	free(s2);
	return (res);
}

char	*make_filled_line(char c, int lenght)
{
	char	*line;
	int	i;

	line = malloc((lenght + 1) * sizeof(char));
	if (line == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < lenght)
	{
		line[i] = c;
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	replace_null_terminated_strings(t_data *data, char **strings)
{
	int	y;
	size_t	line_len;

	y = 0;
	while (strings[y] != NULL)
	{
		line_len = ft_strlen(strings[y]);
		if (line_len < data->map_width)
		{
			strings[y] = ft_strappend(strings[y], make_filled_line(SPACE, data->map_width - line_len));
		}
		y++;
	}
}

void	script_init(t_data *data)
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
			colors_init(data, data->script[y], 'F');
		else if (!ft_strncmp(data->script[y], "C", 1))
			colors_init(data, data->script[y], 'C');
		else if (is_map_line(data->script[y]))
		{
			data->map = &data->script[y];
			assign_map_params(data);
			replace_null_terminated_strings(data, data->map);
			break ;
		}
		else if ((ft_strncmp(data->script[y], "\n", 1)))
		{	
			printf("Invalid stript\n");
			close_event(data);
		}
		y++;
	}
}
