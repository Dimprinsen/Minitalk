/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttinnerh <ttinnerh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:24:16 by ttinnerh          #+#    #+#             */
/*   Updated: 2024/08/04 17:20:20 by ttinnerh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_format(char spec, va_list ap)
{
	int	count;

	count = 0;
	if (spec == 'c')
		count += putchar(va_arg(ap, int));
	else if (spec == 's')
		count += putstr(va_arg(ap, char *));
	else if (spec == 'p')
		count += print_pointer(va_arg(ap, unsigned long));
	else if (spec == 'd' || spec == 'i')
		count += print_digit(va_arg(ap, int));
	else if (spec == 'u')
		count += print_digit(va_arg(ap, unsigned int));
	else if (spec == 'x')
		count += print_hex(va_arg(ap, unsigned int), 'x');
	else if (spec == 'X')
		count += print_hex(va_arg(ap, unsigned int), 'X');
	else if (spec == '%')
		count += putchar('%');
	else
		count += write(1, &spec, 1);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	ap;

	count = 0;
	va_start(ap, str);
	while (*str != '\0')
	{
		if (*str == '%')
			count += check_format(*(++str), ap);
		else
			count += write(1, str, 1);
		str++;
	}
	va_end(ap);
	return (count);
}
/*
int	main(void)
{
	int	count;
	int	*ptr;
	int	a;
	//char	*str;

	//str = 0;
	a = 5;
	ptr = &a;
	count = ft_printf("Hello there %s %c\n", "Thobi", 'T');
	//count = ft_printf("%p\n", ptr);
	//ft_printf("FT_PRINTF: The amount of written chars are %d!\n", count);
	//printf("PRINTF: The amount of written chars are %d!\n", count);
	//printf("OG%%: %x, %X, %d, %p, %u\n", -1, -1, -1, ptr, -500);
	//ft_printf("MY%%: %x, %X, %d, %p, %u\n", -1, -1, -1, ptr, -500);
}

int	main(void)
{
	int	count;
	int	*ptr;
	int	a = 5;

	ptr = &a;

	count = ft_printf("%d\n", count);
	count = printf("%d\n", count);
	ft_printf("FT_PRINTF: The amount of written chars are %d!\n", count);
	printf("OG: The amount of written chars are %d!\n", count);
	printf("OG%%: %x, %X, %d, %p, %u\n", -1, -1, -1, ptr, -500);
	ft_printf("MY%%: %x, %X, %d, %p, %u\n", -1, -1, -1, ptr, -500);
}*/
