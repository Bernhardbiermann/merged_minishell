/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:54:58 by aroux             #+#    #+#             */
/*   Updated: 2025/01/08 17:53:06 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_count(char c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

void	ft_putstr_count(char *s, int *count)
{
	if (s == NULL)
	{
		write(1, "(null)", 6);
		*count = *count + 6;
	}
	else
	{
		while (*s != '\0')
		{
			write(1, s, 1);
			(*count)++;
			s++;
		}
	}
	return ;
}

void	ft_conversion_specifier(va_list args, char c, int *count)
{
	if (c == 'c')
		ft_putchar_count(va_arg(args, int), count);
	else if (c == 's')
		ft_putstr_count(va_arg(args, char *), count);
	else if (c == 'p')
		ft_putptr_count(va_arg(args, void *), count);
	else if (c == 'i' || c == 'd')
		ft_putint_count(va_arg(args, int), count);
	else if (c == 'u')
		ft_putunsigned_count(va_arg(args, unsigned long), count);
	else if (c == 'x' || c == 'X')
		ft_puthex_ct(va_arg(args, unsigned int), c, count);
	else if (c == '%')
	{
		write(1, "%", 1);
		(*count)++;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	char	*ptr;

	count = 0;
	if (format == NULL)
		return (-1);
	va_start(args, format);
	ptr = (char *)format;
	while (*ptr)
	{
		if (*ptr != '%')
		{
			write(2, ptr, 1);
			count++;
		}
		else
		{
			ptr++;
			ft_conversion_specifier(args, *ptr, &count);
		}
		ptr++;
	}
	va_end(args);
	return (count);
}
