/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:58:24 by valeriia          #+#    #+#             */
/*   Updated: 2025/07/16 21:33:49 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

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

static char	*ft_join(char *res, char *s)
{
	while (*s != '\0')
		*res++ = *s++;
	return (res);
}

static char	*ft_strappend(char *s1, char *s2)
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

static char	*make_filled_line(char c, int lenght)
{
	char	*line;
	int		i;

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
	int	line_len;

	y = 0;
	while (strings[y] != NULL)
	{
		line_len = ft_strlen(strings[y]);
		if (line_len < data->map_width)
		{
			strings[y] = ft_strappend(strings[y],
					make_filled_line(SPACE, data->map_width - line_len));
		}
		y++;
	}
}
