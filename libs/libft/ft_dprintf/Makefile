#HEADERS
HEADERS := ft_dprintf.h

#SOURCES
SRCS	:=	ft_dprintf.c \
			ft_dprintf_c.c \
			ft_dprintf_s.c \
			ft_dprintf_d.c \
			ft_dprintf_x.c \
			ft_dprintf_ux.c \
			ft_dprintf_p.c \
			ft_dprintf_u.c \
			ft_dprintf_i.c \
			ft_dprintf_percent.c \
			ft_convert_to_base.c \

#TARGET
NAME := ft_dprintf.a

#OBJECTS
OBJS := $(SRCS:%.c=%.o)

#FLAGS
CC		:= cc -c
CFLAGS	:= -Wall -Werror -Wextra
AR		:= ar rcs

#RULES
all : $(NAME)

$(NAME) : $(OBJS)
	$(AR) $@ $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
