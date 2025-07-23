/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:06:22 by eklymova          #+#    #+#             */
/*   Updated: 2024/10/30 14:44:59 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;

	if (size != 0 && nmemb > ((size_t) -1) / size)
		return (NULL);
	arr = malloc(nmemb * size);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, nmemb * size);
	return (arr);
}
// int	main() {
//     size_t nmemb = 5;  // Number of elements
//     size_t size = sizeof(int);  // Size of each element

//     // Call ft_calloc
//     int *arr = (int *)ft_calloc(nmemb, size);
//     if (arr == NULL) {
//         printf("Memory allocation failed!\n");
//         return 1;
//     }

//     // Print the allocated array values
//     for (size_t i = 0; i < nmemb; i++) {
//         printf("arr[%zu] = %d\n", i, arr[i]);
//     }

//     // Free allocated memory
//     free(arr);
//     return 0;
// }