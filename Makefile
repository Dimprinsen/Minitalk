# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thtinner <thtinner@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/04 22:23:58 by thtinner          #+#    #+#              #
#    Updated: 2026/01/04 16:12:43 by thtinner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC_S = server.c

SRC_C = client.c

OBJ_S = $(SRC_S:%.c=%.o)
OBJ_C = $(SRC_C:%.c=%.o)

FTPRINTF = ft_printf/libftprintf.a

all : server client

$(FTPRINTF):
	@make -C ft_printf

server: $(OBJ_S) $(FTPRINTF)
	$(CC) $(CFLAGS) $(OBJ_S) -Lft_printf -lftprintf -o server

client: $(OBJ_C) $(FTPRINTF)
	$(CC) $(CFLAGS) $(OBJ_C) -Lft_printf -lftprintf -o client

clean:
	@make clean -C ft_printf
	@rm -rf $(OBJ_S) $(OBJ_C)
	@echo "...objs removed."

fclean:	clean
	@make fclean -C ft_printf
	@rm -rf server client
	@echo "...binaries removed."

re:	fclean all

.PHONY:	all clean fclean re
