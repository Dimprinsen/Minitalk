

NAME		= libftprintf.a

CC			= cc

FLAGS		= -Wall -Wextra -Werror 

SRCS		= ft_printf.c ft_printf_util.c libft.c 

OBJS        = $(SRCS:.c=.o)

HEADER		= ft_printf.h

RM			= rm -f

all:		$(NAME)

%.o: %.c $(HEADER)
		$(CC) -c $(FLAGS) -o $@ $<


$(NAME):	$(OBJS)
			ar rc $(NAME) $(OBJS)

$(OBJ_FILE):	$(SRC_FILE)
	cc -Wall -Wextra -Werror -c $(SRC_FILE)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re


