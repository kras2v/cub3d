/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:05:08 by eklymova          #+#    #+#             */
/*   Updated: 2025/08/05 12:44:03 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nbr_len(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
	{
		i = 1;
	}
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	i;
	char	*arr;
	long	num;

	num = n;
	i = nbr_len(num);
	arr = (char *)malloc(sizeof(char) * (nbr_len(num) + 1));
	if (!arr)
		return (NULL);
	arr[i] = '\0';
	if (num < 0)
	{
		arr[0] = '-';
		num = -num;
	}
	if (num == 0)
		arr[0] = '0';
	i -= 1;
	while (num > 0)
	{
		arr[i--] = (num % 10) + '0';
		num /= 10;
	}
	return (arr);
}
