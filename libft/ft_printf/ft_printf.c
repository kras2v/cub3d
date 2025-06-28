/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:04:07 by valeriia          #+#    #+#             */
/*   Updated: 2025/01/09 20:59:24 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

static int	ft_choose_convension(va_list list, const char *format)
{
	if (*format == 'c')
		return (ft_printf_c(va_arg(list, int)));
	else if (*format == 's')
		return (ft_printf_s(va_arg(list, char *)));
	else if (*format == '%')
		return (ft_printf_percent());
	else if (*format == 'd')
		return (ft_printf_d(va_arg(list, int)));
	else if (*format == 'i')
		return (ft_printf_i(va_arg(list, int)));
	else if (*format == 'p')
		return (ft_printf_p(va_arg(list, unsigned long)));
	else if (*format == 'u')
		return (ft_printf_u(va_arg(list, unsigned int)));
	else if (*format == 'x')
		return (ft_printf_x(va_arg(list, unsigned int)));
	else if (*format == 'X')
		return (ft_printf_ux(va_arg(list, unsigned int)));
	return (0);
}

int	ft_printf(const char *format, ...)
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
				len += ft_choose_convension(list, format);
		}
		else
			len += ft_printf_c(*format);
		if (*format)
			format++;
	}
	va_end(list);
	return (len);
}
