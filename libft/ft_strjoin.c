/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:05:30 by eklymova          #+#    #+#             */
/*   Updated: 2025/01/09 13:37:29 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*arr;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	arr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		arr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		arr[i] = s2[j];
		j++;
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
// int main(void)
// {
// 	char s1[] = "hello";
// 	char s2[] = "world!";
// 	printf("%s", ft_strjoin(s1, s2));
// }