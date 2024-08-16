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

SRC_S_BONUS = server_bonus.c

SRC_C_BONUS = client_bonus.c

OBJ_S = $(SRC_S:%.c=%.o)
OBJ_C = $(SRC_C:%.c=%.o)
OBJ_S_BONUS = $(SRC_S_BONUS:%.c=%.o)
OBJ_C_BONUS = $(SRC_C_BONUS:%.c=%.o)

all : server client

server: $(OBJ_S) ft_printf
	@make -C ft_printf
	$(CC) $(CFLAGS) $(OBJ_S) -Lft_printf -lftprintf -o server

client: $(OBJ_C) ft_printf
	@make -C ft_printf
	$(CC) $(CFLAGS) $(OBJ_C) -Lft_printf -lftprintf -o client

bonus: server_bonus client_bonus

server_bonus: $(OBJ_S_BONUS) ft_printf
	@make -C ft_printf
	$(CC) $(CFLAGS) $(OBJ_S_BONUS) -Lft_printf -lftprintf -o server_bonus

client_bonus: $(OBJ_C_BONUS) ft_printf
	@make -C ft_printf
	$(CC) $(CFLAGS) $(OBJ_C_BONUS) -Lft_printf -lftprintf -o client_bonus

ft_printf:
	@make -s -C ft_printf

clean:
	@make clean -C ft_printf
	@rm -rf $(OBJ_S) $(OBJ_C) $(OBJ_S_BONUS) $(OBJ_C_BONUS)
	@echo "...objs removed."

fclean:	clean
	@make fclean -C ft_printf
	@rm -rf server client server_bonus client_bonus
	@echo "...binaries removed."

re:	fclean all

.PHONY:	all clean fclean re bonus
