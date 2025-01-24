/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:54:57 by aroux             #+#    #+#             */
/*   Updated: 2025/01/24 12:04:30 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* concatenates 3 strings. Needs to be freed */
char	*multi_strjoin(char *str1, char *str2, char *str3)
{
	char	*tmp;
	char	*multijoin;

	if (!str1)
		str1 = "";
	if (!str2)
		str2 = "";
	if (!str3)
		str3 = "";
	tmp = ft_strjoin(str1, str2);
	if (!tmp)
		return (NULL);
	multijoin = ft_strjoin(tmp, str3);
	free(tmp);
	if (!multijoin)
		return (NULL);
	return (multijoin);
}

int	is_empty_str(char *str)
{
	if (*str == '\0')
		return (1);
	else
		return (0);
}
