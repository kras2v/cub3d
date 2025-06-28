/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:04:07 by valeriia          #+#    #+#             */
/*   Updated: 2024/10/30 10:55:56 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_assign_str(char *a)
{
	if (!a)
		return ("(null)");
	return (a);
}

int	ft_printf_s(char *a)
{
	char	*res;

	res = ft_assign_str(a);
	ft_putstr_fd(res, 1);
	return (ft_strlen(res));
}
