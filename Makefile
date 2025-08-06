# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 16:22:08 by kvalerii          #+#    #+#              #
#    Updated: 2025/08/06 16:40:26 by eklymova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Project Configuration ---
NAME			= cub3d

LIBS_PATH		= libs
LIBFT_PATH		= $(LIBS_PATH)/libft
LIBFT			= $(LIBFT_PATH)/libft.a
DPRINTF			= $(LIBFT_PATH)/ft_dprintf/ft_dprintf.a

CFLAGS			= -Wall -Werror -Wextra -g
CC				= cc

MINILIBX_DIR	= minilibx_linux
MINILIBX_LIB	= mlx_Linux

BONUS			= bonus
SRCS_BONUS_DIR	= $(BONUS)/srcs_bonus
INCLUDES_BONUS	= $(BONUS)/includes_bonus
OBJS_BONUS_DIR	= $(BONUS)/objs_bonus

MANDATORY		= mandatory
SRCS_DIR		= $(MANDATORY)/srcs
INCLUDES		= $(MANDATORY)/includes
OBJS_DIR		= $(MANDATORY)/objs

# --- Source File Lists ---
SRCS =	main.c \
		events.c \
		data_initializer.c \
		display_game.c \
		error_handler.c \
		dda/dda_color_helpers.c \
		dda/dda_helpers.c \
		dda/dda_raycast.c \
		dda/dda_step.c \
		dda/dda_traversel.c \
		validation/input_validator.c \
		mlx/mlx_handler.c \
		minimap/minimap_utils.c \
		minimap/minimap_draw_utils.c \
		draw_utils/bresenham_line_algorithm.c \
		draw_utils/bresenham_line_utils.c \
		draw_utils/draw_utils.c \
		math/math.c \
		validation/map_validation.c \
		validation/map_char_validation.c \
		validation/map_walls_checker.c \
		validation/map_n_valid.c \
		flashlight/flashlight_utils.c \
		player/movement.c \
		player/player_initialization.c \
		wall_collision/wall_collision.c \
		parser/map_init.c \
		parser/script_init.c \
		parser/script_init_utils.c \


SRCS_BONUS =	main_bonus.c \
				events_bonus.c \
				data_initializer_bonus.c \
				display_game_bonus.c \
				error_handler_bonus.c \
				dda/dda_color_helpers_bonus.c \
				dda/dda_helpers_bonus.c \
				dda/dda_raycast_bonus.c \
				dda/dda_step_bonus.c \
				dda/dda_traversel_bonus.c \
				validation/input_validator_bonus.c \
				mlx/mlx_handler_bonus.c \
				door/door_managment_bonus.c \
				door/door_events_bonus.c \
				minimap/minimap_utils_bonus.c \
				minimap/minimap_draw_utils_bonus.c \
				draw_utils/bresenham_line_algorithm_bonus.c \
				draw_utils/bresenham_line_utils_bonus.c \
				draw_utils/draw_utils_bonus.c \
				math/math_bonus.c \
				validation/map_validation_bonus.c \
				validation/map_char_validation_bonus.c \
				validation/map_walls_checker_bonus.c \
				validation/map_n_valid_bonus.c \
				flashlight/flashlight_utils_bonus.c \
				player/movement_bonus.c \
				player/player_initialization_bonus.c \
				wall_collision/wall_collision_bonus.c \
				parser/map_init_bonus.c \
				parser/script_init_bonus.c \
				parser/script_init_utils_bonus.c \
				animated_sprites/sprites_bonus.c \
				animated_sprites/sprite_utils_bonus.c

# --- Object File Generation ---

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
BONUS_OBJS = $(SRCS_BONUS:%.c=$(OBJS_BONUS_DIR)/%.o)

# --- Make Targets ---

all: $(MINILIBX_DIR)/.git build_mlx $(NAME)

# Target to build MiniLibX
build_mlx:
	$(MAKE) -C $(MINILIBX_DIR)

# Target to initialize Git submodule for MiniLibX
$(MINILIBX_DIR)/.git:
	@git submodule update --init $(MINILIBX_DIR)

# --- Final Executable Linkage ---
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(MINILIBX_DIR) -l$(MINILIBX_LIB) \
	-L/usr/lib -I$(MINILIBX_DIR) -fPIE -lXext -lX11 -lm -lz -o  $(NAME) \
	$(DPRINTF) $(LIBFT)

# Bonus build target
bonus: $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -L$(MINILIBX_DIR) -l$(MINILIBX_LIB) \
	-L/usr/lib -I$(MINILIBX_DIR) -fPIE -lXext -lX11 -lm -lz -o $(NAME) \
	$(DPRINTF) $(LIBFT)

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

# --- Compilation Rules for Object Files ---
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -I$(INCLUDES) -I$(MINILIBX_DIR) -o $@ -c $< $(HEADERS)

$(OBJS_BONUS_DIR)/%.o: $(SRCS_BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -I$(INCLUDES_BONUS) -I$(MINILIBX_DIR) -o $@ -c $< $(HEADERS)

# --- Cleaning Rules ---
clean :
	rm -rf $(OBJS_DIR) $(OBJS_BONUS_DIR)
	make -C $(LIBFT_PATH) clean

fclean : clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re : fclean all

.PHONY : all clean fclean re build_mlx $(LIBFT)