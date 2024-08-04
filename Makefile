# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttinnerh <ttinnerh@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/04 22:23:58 by ttinnerh          #+#    #+#              #
#    Updated: 2024/08/04 22:29:55 by ttinnerh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC_S = server.c

SRC_C = client.c

OBJ_S = $(SRC_S:%.c=%.o)

OBJ_C = $(SRC_C:%.c=%.o)

all : server client

server: $(OBJ_S) ft_printf $(HEADER)
	@make -C ft_printf
	$(CC) $(CFLAGS) $(OBJ_S) -Lft_printf -lftprintf -o server

client: $(OBJ_C) ft_printf $(HEADER)
	@make -C ft_printf
	$(CC) $(CFLAGS) $(OBJ_C) -Lft_printf -lftprintf -o client

ft_printf:
	@make -s -C ft_printf

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
