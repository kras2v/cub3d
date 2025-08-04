/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD
/*   map.h                                              :+:      :+:    :+:   */
=======
/*   map_bonus.h                                        :+:      :+:    :+:   */
>>>>>>> main
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:33:54 by kvalerii          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/28 12:14:46 by kvalerii         ###   ########.fr       */
=======
/*   Updated: 2025/08/01 15:52:48 by kvalerii         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_BONUS_H
# define MAP_BONUS_H

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

<<<<<<< HEAD
# define DOOR_PATH			"./walls/xpm/door.xpm"
=======
# define DOOR_PATH	"./textures/door/door_rainbow.xpm"
>>>>>>> main

#endif