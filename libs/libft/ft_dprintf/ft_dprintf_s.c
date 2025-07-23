/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmzvr <rmzvr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:04:07 by valeriia          #+#    #+#             */
/*   Updated: 2025/04/25 11:46:50 by rmzvr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static char	*ft_assign_str(char *a)
{
	if (!a)
		return ("(null)");
	return (a);
}

int	ft_dprintf_s(int fd, char *a)
{
	char	*res;

	res = ft_assign_str(a);
	ft_putstr_fd(res, fd);
	return (ft_strlen(res));
}
