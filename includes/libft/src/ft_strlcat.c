/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:54:05 by aroux             #+#    #+#             */
/*   Updated: 2024/05/03 12:03:29 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;

	srclen = 0;
	destlen = 0;
	i = 0;
	while (src[srclen] != '\0')
		srclen++;
	while (dst[destlen] != '\0' && destlen < size)
		destlen++;
	if (size == 0 || dst[destlen] != '\0')
		return (size + srclen);
	while (src[i] != '\0' && i + destlen < size - 1)
	{
		dst[destlen + i] = src[i];
		i++;
	}
	dst[destlen + i] = '\0';
	return (srclen + destlen);
}
