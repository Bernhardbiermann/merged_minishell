/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:38:28 by aroux             #+#    #+#             */
/*   Updated: 2024/09/19 16:13:22 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lensplit(const char *str, char c)
{
	int	length;

	length = 0;
	while (str[length] != '\0' && str[length] != c)
		length++;
	return (length);
}

int	ft_count_nbsplit(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		while (*str == c)
			str++;
		if (*str != '\0' && *str != c)
			count++;
		while (*str != '\0' && *str != c)
			str++;
	}
	return (count);
}

static char	**ft_fillsplt(char **splits, char c, const char *s, size_t nb_split)
{
	size_t	i;

	while (*s != '\0' && *s == c)
		s++;
	i = 0;
	while (i < nb_split)
	{
		while (*s != '\0' && *s == c)
			s++;
		splits[i] = ft_substr(s, 0, ft_lensplit(s, c));
		if (splits[i] == NULL)
		{
			while (i > 0)
			{
				free(splits[i - 1]);
				i--;
			}
			free(splits);
			return (NULL);
		}
		s = s + ft_lensplit(s, c);
		i++;
	}
	splits[i] = NULL;
	return (splits);
}

char	**ft_split(char const *s, char c)
{
	size_t	nb_split;
	char	**splits;

	nb_split = ft_count_nbsplit(s, c);
	splits = malloc ((nb_split + 1) * sizeof(char *));
	if (splits == NULL)
		return (NULL);
	return (ft_fillsplt(splits, c, s, nb_split));
}
