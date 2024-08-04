/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttinnerh <ttinnerh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:06:53 by ttinnerh          #+#    #+#             */
/*   Updated: 2024/08/04 21:07:33 by ttinnerh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "ft_printf/ft_printf.h"

void	bit_handler(int bit)
{
	static int	i = 0;
	static char	current = 0;

	if (bit == SIGUSR1)
		current |= (0x01 << i);
	i++;
	if (i == 8)
	{
		if (current == '\0')
		{
			ft_printf("\n");
			current = 0;
			i = 0;
		}
		else if (current != '\0')
		{
			ft_printf("%c", current);
			current = 0;
			i = 0;
		}
	}
}

/*int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	signal(SIGUSR1, bit_handler);
	signal(SIGUSR2, bit_handler);
	while (1)
	{
		pause();
	}
	return (0);
}*/

int	main(int argc, char **argv)
{
	int	pid;

	(void)argv;
	if (argc != 1)
	{
		printf("Error\n");
		return (1);
	}
	signal(SIGUSR1, bit_handler);
	signal(SIGUSR2, bit_handler);
	pid = getpid();
	printf("%d\n", pid);
	while (argc == 1)
	{
		pause ();
	}
	return (0);
}