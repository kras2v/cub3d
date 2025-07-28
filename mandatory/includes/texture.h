/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:04:32 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/28 12:10:31 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

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