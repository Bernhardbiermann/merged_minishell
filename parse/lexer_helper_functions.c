/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:46:03 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/27 12:31:51 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strncpy(char *src, char *start, char *end)
{
	size_t	newstr_len;
	char	*newstr;
	size_t	i;

	if (!src || !start || !end || start >= end)
		return (NULL);
	i = 0;
	newstr_len = end - start;
	newstr = malloc(sizeof(char) * (newstr_len + 1));
	if (!newstr)
		return (NULL);
	while (i < newstr_len)
	{
		newstr[i] = start[i];
		i++;
	}
	newstr[newstr_len] = '\0';
	return (newstr);
}

char	*ft_strndup(const char *s, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0' && i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

char	*ft_strstr(char *big, char *little)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] != '\0')
	{
		j = 0;
		while (big[i + j] != '\0' && big[i + j] == little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}

char	*find_end(char *start)
{
	char	*end;

	if (!start)
		return (NULL);
	end = start;
	if (!(*end) || (!ft_isalnum(*end) && (*end) != '_'))
		return (NULL);
	while (*end && (ft_isalnum(*end) || *end == '_'))
		end++;
	return (end);
}

char	*replace_substring(char *original, char *to_replace, char *replacement)
{
	char	*position;
	char	*new_str;
	size_t	to_replace_len;
	size_t	new_range;
	size_t	prefix_len;

	new_str = NULL;
	if (!original || !to_replace || !replacement)
		return (0);
	to_replace_len = ft_strlen(to_replace);
	new_range = ft_strlen(original) - to_replace_len + ft_strlen(replacement);
	new_str = malloc(sizeof(char) * (new_range + 1));
	if (!new_str)
		return (NULL);
	position = ft_strstr(original, to_replace);
	prefix_len = position - original;
	ft_memcpy(new_str, original, prefix_len);
	ft_memcpy(new_str + prefix_len, replacement, ft_strlen(replacement));
	ft_memcpy(new_str + prefix_len + ft_strlen(replacement), position \
	+ to_replace_len, ft_strlen(original) - prefix_len - to_replace_len);
	new_str[new_range] = '\0';
	to_replace = new_str;
	free(new_str);
	return (to_replace);
}
