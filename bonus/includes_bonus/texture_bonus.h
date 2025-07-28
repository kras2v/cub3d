/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:04:32 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/28 12:15:24 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_BONUS_H
# define TEXTURE_BONUS_H

# include "image.h"

typedef enum e_direction
{
	N,
	E,
	S,
	W,
	D
}	t_direction;

typedef struct s_texture_params
{
	t_image	image;
	char	*name;
	int		width;
	int		height;
}	t_texture_params;

#endif