/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:05:32 by eklymova          #+#    #+#             */
/*   Updated: 2024/10/29 15:06:53 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s || !f)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
// char to_upp(char c) 
// {
//     if (c >= 'a' && c <= 'z') 
// 	{
//         return c - 32;
//     }
//     return c;
// }

// int main() 
// {
//     const char *str = "hello, world!";
//     printf("Original string: %s\n", str);
//     char *transformed_str = ft_strmapi(str, to_upp);
//     if (transformed_str)
// 	{
//         printf("Transformed string: %s\n", transformed_str);
//     }
// }