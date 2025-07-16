/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:33:54 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/16 16:47:26 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

typedef enum e_colors
{
	RED			= 0x00FF0000,
	GREEN		= 0x0000FF00,
	BLUE		= 0x000000FF,
	LIGHT_BLUE	= 0x0080B0FF,
	WHITE		= 0x00FFFFFF,
	BLACK		= 0x00000000,
	YELLOW		= 0x00FFFF00,
	CYAN		= 0x0000FFFF,
	MAGENTA		= 0x00FF00FF,
	ORANGE		= 0x00FFA500,
	PURPLE		= 0x00800080,
	GRAY		= 0x00808080,
	LIGHT_GRAY	= 0x00D3D3D3,
	DARK_GRAY	= 0x00404040,
	BROWN		= 0x00A52A2A,
	PINK		= 0x00FFC0CB,
	TURQUOISE	= 0x0040E0D0,
	GOLD		= 0x00FFD700
}	t_colors;

#endif