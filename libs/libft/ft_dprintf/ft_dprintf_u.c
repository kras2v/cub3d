/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmzvr <rmzvr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:04:07 by valeriia          #+#    #+#             */
/*   Updated: 2025/04/25 11:46:58 by rmzvr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dprintf_u(int fd, unsigned int dec)
{
	char	*base;

	base = "0123456789";
	return (ft_convert_to_base(fd, dec, base, ft_strlen(base)));
}
