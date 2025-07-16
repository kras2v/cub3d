# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 16:22:08 by kvalerii          #+#    #+#              #
#    Updated: 2025/07/16 22:33:59 by valeriia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = dda
MINILIBX_DIR = minilibx_linux
MINILIBX_LIB = mlx_Linux
OBJS_DIR  = objs
CFLAGS := -Wall -Werror -Wextra -g
CC := clang
SRC_DIR := ./srcs

SRCS =	main.c \
		dda_color_helpers.c \
		dda_helpers.c \
		dda_raycast.c \
		dda_step.c \
		dda_traversel.c \
		minimap_utils.c \
		minimap_draw_utils.c \
		bresenham_line_algorithm.c \
		draw_utils.c \
		movement.c \
		events.c \
		free_utils.c \
		math.c \
		map_init.c \
		map_valid.c \
		flashlight_utils.c \
		player_initialization.c \
		wall_colision.c \
		script_init.c \
		script_init_utils.c

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
	$(CC) $(CFLAGS) $(OBJS) -L$(MINILIBX_DIR) -l$(MINILIBX_LIB) -L/usr/lib -I$(MINILIBX_DIR) -fPIE -lXext -lX11 -lm -lz -o $(NAME) libft/libft.a


clean :
	rm -rf $(OBJS_DIR)
	make -C libft clean

fclean : clean
	rm -f $(NAME)
	make -C libft fclean

re : fclean all

.PHONY : all clean fclean re build_mlx libft/libft.a

