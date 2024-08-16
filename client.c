/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttinnerh <ttinnerh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:06:36 by ttinnerh          #+#    #+#             */
/*   Updated: 2024/08/08 20:02:03 by ttinnerh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "ft_printf/ft_printf.h"

volatile sig_atomic_t	g_ack_received = 0;

void	sig_fail(int pid)
{
	ft_printf("Failed to send signal to PID %d\n", pid);
	exit(EXIT_FAILURE);
}

void	mess_comp(int signum)
{
	(void)signum;
	ft_printf("Signal received!\n");
}

void	ack_handler(int signum)
{
	(void)signum;
	g_ack_received = 1;
}

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
			{
				if (kill(pid, SIGUSR1) == -1)
					sig_fail(pid);
			}
			else if (kill(pid, SIGUSR2) == -1)
				sig_fail(pid);
			bit++;
			usleep(300);
		}
		while (!g_ack_received)
			pause();
		g_ack_received = 0;
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
	if (pid < 1000)
	{
		ft_printf("Invalid server PID: %s\n", argv[1]);
		return (1);
	}
	message = argv[2];
	signal(SIGUSR1, ack_handler);
	signal(SIGUSR2, mess_comp);
	send_message(pid, message);
	return (0);
}
