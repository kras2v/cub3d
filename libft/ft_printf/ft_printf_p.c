/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:04:07 by valeriia          #+#    #+#             */
/*   Updated: 2024/10/30 11:22:19 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_handle_null(void)
{
	char	*res;

	res = "(nil)";
	ft_putstr_fd(res, 1);
	return (ft_strlen(res));
}

int	ft_printf_p(unsigned long dec)
{
	if (!dec)
		return (ft_handle_null());
	ft_putstr_fd("0x", 1);
	return (2 + ft_printf_x(dec));
}
