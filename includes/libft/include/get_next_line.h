/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:45:20 by aroux             #+#    #+#             */
/*   Updated: 2024/08/23 12:10:44 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

size_t	is_newline_lenline(char *s);
char	*clean_stash(char *str);
char	*get_next_line(int fd);

#endif
