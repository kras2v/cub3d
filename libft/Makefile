CC 	=  cc
CFLAGS = -Wall -Wextra -Werror -g
OBJS_DIR  = objs

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

# SRCS_ALL = $(SRCS) $(SRCSB)

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

OBJS_B = $(SRCSB:.c=.o)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< 

NAME = libft.a

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)	
# archive, replace, create 

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

all : $(NAME)


bonus : $(OBJS) $(OBJS_B)
	ar rc $(NAME) $(OBJS) $(OBJS_B)


clean : 
	rm -rf $(OBJS_DIR)
	rm -f $(OBJS) $(OBJS_B)

fclean : clean
	rm -f $(NAME)

re : fclean all 

.PHONY: all clean fclean re bonus
