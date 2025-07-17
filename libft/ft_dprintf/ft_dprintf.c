/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmzvr <rmzvr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:04:07 by valeriia          #+#    #+#             */
/*   Updated: 2025/04/25 11:46:53 by rmzvr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	ft_is_conversion(const char a)
{
	return (a == 'c'
		|| a == 's'
		|| a == 'p'
		|| a == 'd'
		|| a == 'i'
		|| a == 'u'
		|| a == 'x'
		|| a == 'X'
		|| a == '%');
}

static int	ft_choose_convension(int fd, va_list list, const char *format)
{
	if (*format == 'c')
		return (ft_dprintf_c(fd, va_arg(list, int)));
	else if (*format == 's')
		return (ft_dprintf_s(fd, va_arg(list, char *)));
	else if (*format == '%')
		return (ft_dprintf_percent(fd));
	else if (*format == 'd')
		return (ft_dprintf_d(fd, va_arg(list, int)));
	else if (*format == 'i')
		return (ft_dprintf_i(fd, va_arg(list, int)));
	else if (*format == 'p')
		return (ft_dprintf_p(fd, va_arg(list, unsigned long)));
	else if (*format == 'u')
		return (ft_dprintf_u(fd, va_arg(list, unsigned int)));
	else if (*format == 'x')
		return (ft_dprintf_x(fd, va_arg(list, unsigned int)));
	else if (*format == 'X')
		return (ft_dprintf_ux(fd, va_arg(list, unsigned int)));
	return (0);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	list;
	int		len;

	len = 0;
	va_start(list, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (ft_is_conversion(*format))
				len += ft_choose_convension(fd, list, format);
		}
		else
			len += ft_dprintf_c(fd, *format);
		if (*format)
			format++;
	}
	va_end(list);
	return (len);
}
