/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_x.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmzvr <rmzvr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:04:07 by valeriia          #+#    #+#             */
/*   Updated: 2025/04/25 11:46:30 by rmzvr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dprintf_x(int fd, unsigned long dec)
{
	char	*base;

	base = "0123456789abcdef";
	return (ft_convert_to_base(fd, dec, base, ft_strlen(base)));
}
