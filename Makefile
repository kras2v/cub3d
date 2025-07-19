# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 16:22:08 by kvalerii          #+#    #+#              #
#    Updated: 2025/07/22 14:11:24 by kvalerii         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = dda
MINILIBX_DIR = minilibx_linux
MINILIBX_LIB = mlx_Linux
OBJS_DIR  = objs
# CFLAGS := -Wall -Werror -Wextra -g
CC := cc
SRC_DIR := ./srcs

SRCS =	main.c \
		dda_color_helpers.c \
		dda_helpers.c \
		dda_raycast.c \
		dda_step.c \
		dda_traversel.c \
		display_game.c \
		error_handler.c \
		input_validator.c \
		mlx_handler.c \
		data_initializer.c \
		minimap_utils.c \
		minimap_draw_utils.c \
		bresenham_line_algorithm.c \
		bresenham_line_utils.c \
		draw_utils.c \
		movement.c \
		events.c \
		math.c \
		map_init.c \
		door_managment.c \
		map_validation.c \
		map_char_validation.c \
		map_walls_checker.c \
		sprites.c \
		flashlight_utils.c \
		player_initialization.c \
		wall_colision.c \
		script_init.c \
		script_init_utils.c \
		sprite_utils.c

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

all: $(MINILIBX_DIR)/.git build_mlx $(NAME)

build_mlx:
	$(MAKE) -C $(MINILIBX_DIR)

$(MINILIBX_DIR)/.git:
	@git submodule update --init $(MINILIBX_DIR)

libft/libft.a:
	$(MAKE) -C libft

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I$(MINILIBX_DIR) -o $@ -c $< $(HEADERS)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) -L$(MINILIBX_DIR) -l$(MINILIBX_LIB) -L/usr/lib -I$(MINILIBX_DIR) -fPIE -lXext -lX11 -lm -lz -o $(NAME) libft/ft_dprintf/ft_dprintf.a libft/libft.a

clean :
	rm -rf $(OBJS_DIR)
	make -C libft clean

fclean : clean
	rm -f $(NAME)
	make -C libft fclean

re : fclean all

.PHONY : all clean fclean re build_mlx libft/libft.a

