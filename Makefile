# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 16:22:08 by kvalerii          #+#    #+#              #
#    Updated: 2025/06/25 20:33:35 by kvalerii         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = dda
MINILIBX_DIR = minilibx_linux
MINILIBX_LIB = mlx_Linux
OBJS_DIR  = objs
CFLAGS := -Wall -Werror -Wextra
CC := clang -g
SRC_DIR := .

SRCS =	dda_test.c \
		tools.c \
		minimap_utils.c \
		draw_utils.c \
		movement.c \
		events.c \
		free_utils.c \
		math.c

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

all: $(MINILIBX_DIR)/.git build_mlx $(NAME)

build_mlx:
	$(MAKE) -C $(MINILIBX_DIR)

$(MINILIBX_DIR)/.git:
	@git submodule update --init $(MINILIBX_DIR)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I$(MINILIBX_DIR) -o $@ -c $< $(HEADERS)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(MINILIBX_DIR) -l$(MINILIBX_LIB) -L/usr/lib -I$(MINILIBX_DIR) -fPIE -lXext -lX11 -lm -lz -o $(NAME)


# %.o: %.c
#   $(CC) $(CFLAGS) -fPIE -I/usr/include -Iminilibx_linux -O3 -c $< -o $@

clean :
	rm -rf $(OBJS_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re build_mlx

