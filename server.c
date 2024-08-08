/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttinnerh <ttinnerh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:06:53 by ttinnerh          #+#    #+#             */
/*   Updated: 2024/08/08 20:01:03 by ttinnerh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "ft_printf/ft_printf.h"

void	send_ack(int client_pid)
{
	kill(client_pid, SIGUSR1);
}

void	bit_handler(int signum, siginfo_t *info, void *context)
{
	static int	i = 0;
	static char	current = 0;
	int			client_pid;

	(void)context;
	client_pid = info->si_pid;
	if (signum == SIGUSR1)
		current |= (0x01 << i);
	i++;
	if (i == 8)
	{
		if (current == '\0')
		{
			ft_printf("\n");
		}
		else if (current != '\0')
		{
			ft_printf("%c", current);
		}
		current = 0;
		i = 0;
	}
	send_ack(client_pid);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = bit_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
