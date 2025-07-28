/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:33:54 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/28 12:10:45 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDA_BONUS_H
# define DDA_BONUS_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <math.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>

# include "colors_bonus.h"
# include "events_bonus.h"
# include "../libft/libft.h"

# define CELL_SIZE 35
# define MINI_TILE 15
# define MINIMAP_RADIUS 15
# define MINIMAP_OFFSET_X 35
# define MINIMAP_OFFSET_Y 25

typedef enum e_characters
{
	EMPTY = '0',
	WALL = '1',
	SPACE = ' ',
	END = '\0',
	NEW_LINE = '\n',
	EAST = 'E',
	WEST = 'W',
	SOUTH = 'S',
	NORTH = 'N',
	DOOR = 'D',
	SPRITE = '2'
}	t_characters;

# define DOOR_PATH			"./walls/xpm/door.xpm"

#endif