/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttinnerh <ttinnerh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:06:36 by ttinnerh          #+#    #+#             */
/*   Updated: 2024/08/04 22:43:51 by ttinnerh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "ft_printf/ft_printf.h"

void	send_message(int pid, char *str)
{
	int	bit;
	int	i;

	i = 0;
	while (i <= ft_strlen(str))
	{
		bit = 0;
		while (bit < 8)
		{
			if ((str[i] >> bit) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit++;
			usleep(300);
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int		pid;
	char	*message;

	if (argc != 3)
	{
		ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	message = argv[2];
	send_message(pid, message);
	return (0);
}
