#include "libft.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoin_gnl(char *s, char *buff)
{
	char	*arr;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	arr = (char *)malloc((ft_strlen(s) + ft_strlen(buff) + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		arr[i] = s[i];
		i++;
	}
	j = 0;
	while (buff[j] != '\0')
		arr[i++] = buff[j++];
	arr[i] = '\0';
	return (free(s), arr);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*get_n_line(char *s)
{
	char	*arr;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	arr = (char *)malloc((i + 2) * sizeof(char));
	if (!arr)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		arr[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char	*new_string(char *s)
{
	int		i;
	int		j;
	char	*arr;

	i = 0;
	if (!s)
		return (NULL);
	while (s && (s[i] != '\0' && s[i] != '\n'))
		i++;
	if (!s)
		return (free(s), s = NULL, NULL);
	arr = (char *)malloc(((ft_strlen(s) - i) + 1) * sizeof(char));
	if (!arr)
		return (free(s), s = NULL, NULL);
	if (s[i] == '\n')
		i++;
	j = 0;
	while (s[i] != '\0')
		arr[j++] = s[i++];
	arr[j] = '\0';
	return (free(s), s = NULL, arr);
}

char	*read_str(int fd, char *s)
{
	char		*buff;
	ssize_t		bytes;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes = BUFFER_SIZE;
	while ((!ft_strchr_gnl(s, '\n')) && bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1 || (!bytes && s[0] == '\0'))
			return (free(buff), NULL);
		buff[bytes] = '\0';
		s = ft_strjoin_gnl(s, buff);
		if (!s)
			return (free(buff), NULL);
	}
	return (free(buff), s);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*s = NULL;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!s)
	{
		s = malloc(1);
		if (!s)
			return (free(s), s = NULL, NULL);
		s[0] = '\0';
	}
	temp = read_str(fd, s);
	if (!temp)
		return (free(s), s = NULL, NULL);
	s = temp;
	line = get_n_line(s);
	if (!line)
		return (free(s), s = NULL, NULL);
	s = new_string(s);
	if (!s)
		return (free(line), line = NULL, NULL);
	return (line);
}