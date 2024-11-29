/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:17:25 by aroux             #+#    #+#             */
/*   Updated: 2024/08/23 15:53:28 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>
# include "libft.h"

void	ft_putchar_count(char c, int *count);
void	ft_putstr_count(char *s, int *count);
void	ft_putint_count(int n, int *count);
void	ft_putunsigned_count(unsigned int n, int *count);
void	ft_puthex_ct(unsigned long n, char c, int *count);
void	ft_putptr_count(void *ptr, int *count);
void	ft_conversion_specifier(va_list args, char c, int *count);
int		ft_printf(const char *format, ...);

#endif
