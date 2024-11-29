/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnumbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:20:39 by aroux             #+#    #+#             */
/*   Updated: 2024/05/08 16:55:48 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putint_count(int n, int *count)
{
	int	digit;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*count) = (*count) + 11;
		return ;
	}
	else if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		(*count)++;
	}
	if (n >= 10)
		ft_putint_count(n / 10, count);
	digit = n % 10 + '0';
	write(1, &digit, 1);
	(*count)++;
}

void	ft_putunsigned_count(unsigned int n, int *count)
{
	int	digit;

	if (n >= 10)
	{
		ft_putint_count(n / 10, count);
	}
	digit = n % 10 + '0';
	write(1, &digit, 1);
	(*count)++;
}

void	ft_puthex_ct(unsigned long n, char c, int *count)
{
	int		digit;
	char	digit_print;

	if (n >= 16)
		ft_puthex_ct(n / 16, c, count);
	digit = n % 16;
	if (digit < 10)
		digit_print = digit + '0';
	else if (c == 'x')
		digit_print = digit + 'a' - 10;
	else if (c == 'X')
		digit_print = digit + 'A' - 10;
	write(1, &digit_print, 1);
	(*count)++;
}

void	ft_putptr_count(void *ptr, int *count)
{
	unsigned long	n;

	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		*count = *count + 5;
		return ;
	}
	n = (unsigned long)ptr;
	write(1, "0x", 2);
	*count = *count + 2;
	ft_puthex_ct(n, 'x', count);
}
