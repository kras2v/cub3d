/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:33:54 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/28 12:11:26 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

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