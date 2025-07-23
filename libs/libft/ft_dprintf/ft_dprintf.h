/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:04:10 by valeriia          #+#    #+#             */
/*   Updated: 2025/07/17 11:20:18 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include "../libft.h"
# include <stdarg.h>

int	ft_dprintf(int fd, const char *format, ...);
int	ft_dprintf_c(int fd, char a);
int	ft_dprintf_s(int fd, char *a);
int	ft_dprintf_d(int fd, int num);
int	ft_dprintf_i(int fd, int num);
int	ft_dprintf_percent(int fd);
int	ft_dprintf_u(int fd, unsigned int dec);
int	ft_dprintf_x(int fd, unsigned long dec);
int	ft_dprintf_ux(int fd, unsigned long dec);
int	ft_dprintf_p(int fd, unsigned long dec);
int	ft_convert_to_base(
		int fd, unsigned long dec, char *base, size_t base_len);

#endif