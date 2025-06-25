/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:06:29 by eklymova          #+#    #+#             */
/*   Updated: 2024/10/29 14:24:46 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmpsrc;
	unsigned char	*tmpdest;

	tmpsrc = (unsigned char *)src;
	tmpdest = (unsigned char *)dest;
	if (tmpsrc == tmpdest || n == 0)
		return (dest);
	if (tmpsrc < tmpdest && tmpdest < tmpsrc + n)
	{
		while (n > 0)
		{
			tmpdest[n - 1] = tmpsrc[n - 1];
			n--;
		}
	}
	else
	{
		while (n > 0)
		{
			*tmpdest++ = *tmpsrc++;
			n--;
		}
	}
	return (dest);
}
// int	main(void)
// {
// 	char src[] = "12345";
// 	char dest[20] = "1234567";
// 	ft_memmove(dest + 2, src, 5);
// 	// printf("%s", (char *)ft_memmove(dest + 2, src, 5));
// 	printf("%s\n", dest);
// }