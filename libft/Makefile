CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g
OBJS_DIR = objs
DPRINTF  = ./ft_dprintf
DPRINTF_LIB = $(DPRINTF)/ft_dprintf.a

SRCS =  ft_memset.c		\
		ft_bzero.c		\
		ft_memcpy.c		\
		ft_memmove.c 	\
		ft_memchr.c		\
		ft_memcmp.c		\
		ft_strlen.c		\
		ft_isalpha.c 	\
		ft_isdigit.c	\
		ft_isalnum.c	\
		ft_isascii.c	\
		ft_isprint.c	\
		ft_toupper.c	\
		ft_tolower.c	\
		ft_strchr.c		\
		ft_strrchr.c	\
		ft_strncmp.c	\
		ft_strlcpy.c	\
		ft_strlcat.c	\
		ft_strnstr.c	\
		ft_atoi.c		\
		ft_calloc.c		\
		ft_strdup.c		\
		ft_substr.c		\
		ft_strjoin.c 	\
		ft_putchar_fd.c	\
		ft_putstr_fd.c	\
		ft_putendl_fd.c	\
		ft_putnbr_fd.c  \
		ft_strtrim.c	\
		ft_striteri.c   \
		ft_strmapi.c	\
		ft_itoa.c		\
		ft_split.c		\
		get_next_line.c

SRCSB = ft_lstnew_bonus.c		\
		ft_lstadd_front_bonus.c	\
		ft_lstsize_bonus.c		\
		ft_lstlast_bonus.c		\
		ft_lstadd_back_bonus.c	\
		ft_lstdelone_bonus.c		\
		ft_lstiter_bonus.c		\
		ft_lstclear_bonus.c		\
		ft_lstmap_bonus.c

OBJS   = $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_B = $(SRCSB:%.c=$(OBJS_DIR)/%.o)

NAME = libft.a

all: $(NAME)

$(NAME): $(DPRINTF_LIB) $(OBJS)
	ar rc $(NAME) $(OBJS) $(DPRINTF_LIB)

$(DPRINTF_LIB):
	$(MAKE) -C $(DPRINTF)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

bonus: $(DPRINTF_LIB) $(OBJS) $(OBJS_B)
	ar rc $(NAME) $(OBJS) $(OBJS_B) $(DPRINTF_LIB)

clean:
	rm -rf $(OBJS_DIR)
	make -C $(DPRINTF) clean

fclean: clean
	rm -f $(NAME)
	make -C $(DPRINTF) fclean

re: fclean all

.PHONY: all clean fclean re bonus
