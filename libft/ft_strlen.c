/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:04:10 by eklymova          #+#    #+#             */
/*   Updated: 2024/10/29 14:27:06 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	lenth;

	lenth = 0;
	while (s[lenth] != '\0')
	{
		lenth++;
	}
	return (lenth);
}
// int main(void)
// {
// 	char s[] = "hello";
// 	printf("%d", ft_strlen(s));
// }