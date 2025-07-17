/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:05:35 by eklymova          #+#    #+#             */
/*   Updated: 2025/07/17 10:55:38 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*arr;
	int		start;
	int		end;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (ft_strrchr(set, s1[end - 1]) && end > start)
		end--;
	arr = (char *)malloc((end - start + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	ft_strlcpy(arr, &s1[start], end - start + 1);
	return (arr);
}
