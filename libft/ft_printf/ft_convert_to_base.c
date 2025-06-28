/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_to_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:42:32 by kvalerii          #+#    #+#             */
/*   Updated: 2024/10/30 11:31:44 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_convert_to_base(unsigned long dec, char *base, size_t base_len)
{
	char	c;
	int		a;

	a = 1;
	if (dec >= (unsigned long)base_len)
	{
		a = a + ft_convert_to_base(dec / base_len, base, base_len);
	}
	c = base[dec % base_len];
	ft_putchar_fd(c, 1);
	return (a);
}
