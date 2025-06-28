/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:04:10 by valeriia          #+#    #+#             */
/*   Updated: 2024/12/27 12:07:28 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h" 
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_printf_c(char a);
int	ft_printf_s(char *a);
int	ft_printf_d(int num);
int	ft_printf_i(int num);
int	ft_printf_f(double num);
int	ft_printf_percent(void);
int	ft_printf_u(unsigned int dec);
int	ft_printf_x(unsigned long dec);
int	ft_printf_ux(unsigned long dec);
int	ft_printf_p(unsigned long dec);
int	ft_convert_to_base(unsigned long dec, char *base, size_t base_len);

#endif