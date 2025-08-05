/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:05:23 by eklymova          #+#    #+#             */
/*   Updated: 2025/08/05 13:24:15 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(const char *s, char c)
{
	size_t	counter;
	size_t	word;

	counter = 0;
	word = 0;
	while (*s)
	{
		if (*s != c && !word)
		{
			counter++;
			word = 1;
		}
		else if (*s == c)
			word = 0;
		s++;
	}
	return (counter);
}

static char	**ft_free(char **arr, size_t i)
{
	while (i > 0)
	{
		i--;
		free(arr[i]);
	}
	free(arr);
	return (NULL);
}

static size_t	word_length(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	arr = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (word_length(s, c) > 0)
		{
			arr[i] = ft_substr(s, 0, word_length(s, c));
			if (!arr[i])
				return (ft_free(arr, i));
			s += word_length(s, c);
			i++;
		}
	}
	arr[i] = NULL;
	return (arr);
}
