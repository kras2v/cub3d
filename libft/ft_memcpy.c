/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:19:28 by eklymova          #+#    #+#             */
/*   Updated: 2024/10/29 14:24:34 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmpsrc;
	unsigned char	*tmpdest;

	i = 0;
	if (src == NULL && dest == NULL)
		return (NULL);
	tmpsrc = (unsigned char *)src;
	tmpdest = (unsigned char *)dest;
	while (i < n)
	{
		tmpdest[i] = tmpsrc[i];
		i++;
	}
	return (dest);
}
// int	main(void)
// {
// 	char src[] = "hello";
// 	char dest[] = "world";
// 	printf("%s", (char *)ft_memcpy(dest, src, 2));
// }