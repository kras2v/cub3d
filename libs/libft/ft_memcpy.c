/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:19:28 by eklymova          #+#    #+#             */
/*   Updated: 2025/07/17 10:54:42 by kvalerii         ###   ########.fr       */
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
