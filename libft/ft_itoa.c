/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:05:08 by eklymova          #+#    #+#             */
/*   Updated: 2024/10/29 14:44:25 by eklymova         ###   ########.fr       */
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
// int main() 
// {
//     int numbers[] = {0, 42, -42, 123456, -123456, -2147483648, 2147483647};
//     size_t count = sizeof(numbers) / sizeof(numbers[0]);

//     for (size_t i = 0; i < count; i++) {
//         char *str = ft_itoa(numbers[i]);
//         if (str) {
//             printf("ft_itoa(%d) = \"%s\"\n", numbers[i], str);
//         } else {
//             printf("ft_itoa(%d) failed to allocate memory.\n", numbers[i]);
//         }
//     }
//     return 0;
// }