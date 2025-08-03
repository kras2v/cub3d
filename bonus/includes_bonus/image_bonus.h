/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 09:17:38 by valeriia          #+#    #+#             */
/*   Updated: 2025/08/03 11:24:14 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_BONUS_H
# define IMAGE_BONUS_H

# define WIDTH 1980
# define HEIGHT 1220

typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

#endif