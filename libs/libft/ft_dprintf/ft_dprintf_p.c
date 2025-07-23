/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmzvr <rmzvr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:04:07 by valeriia          #+#    #+#             */
/*   Updated: 2025/04/25 11:46:26 by rmzvr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	ft_handle_null(int fd)
{
	char	*res;

	res = "(nil)";
	ft_putstr_fd(res, fd);
	return (ft_strlen(res));
}

int	ft_dprintf_p(int fd, unsigned long dec)
{
	if (!dec)
		return (ft_handle_null(fd));
	ft_putstr_fd("0x", 1);
	return (2 + ft_dprintf_x(fd, dec));
}
