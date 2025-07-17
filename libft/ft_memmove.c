/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:06:29 by eklymova          #+#    #+#             */
/*   Updated: 2025/07/17 10:54:45 by kvalerii         ###   ########.fr       */
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
