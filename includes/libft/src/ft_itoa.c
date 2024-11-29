/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:39:56 by aroux             #+#    #+#             */
/*   Updated: 2024/05/03 11:52:12 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits_sign(int n)
{
	int	count;

	if (n == -2147483648)
	{
		count = 11;
		return (count);
	}
	count = 0;
	if (n <= 0)
	{
		n = -n;
		count++;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		count_ds;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	count_ds = ft_count_digits_sign(n);
	number = malloc((count_ds + 1) * sizeof(char));
	if (number == NULL)
		return (NULL);
	number[count_ds] = '\0';
	if (n < 0)
	{
		number[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		number[count_ds - 1] = n % 10 + '0';
		n = n / 10;
		count_ds--;
	}
	return (number);
}
