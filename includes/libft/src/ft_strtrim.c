/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:48:16 by aroux             #+#    #+#             */
/*   Updated: 2024/05/03 12:04:18 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	i;
	size_t	start;
	size_t	len_s1;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	len_s1 = ft_strlen(s1);
	while (ft_strchr(set, s1[start]) && len_s1 > start)
		start++;
	while (ft_strchr(set, s1[len_s1 - 1]) && len_s1 > start)
		len_s1--;
	trim = malloc((len_s1 - start + 1) * sizeof(char));
	if (trim == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && len_s1 > i + start)
	{
		trim[i] = s1[i + start];
		i++;
	}
	trim[i] = '\0';
	return (trim);
}
