/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:04:18 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/17 13:30:23 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	read_heredoc(t_shell *data)
{
	char	*line;

	setup_signal(HEREDOC);
	while(1)
	{
		line = readline(">");
		if (!line)
		{
			printf("minishell: warning: here-document delimited by end-of-file \
			(wanted '`%s')", data->hdoc->value);
			break ;
		}
		else if (ft_strchr(line, data->hdoc->value) == 0)
			break ;
		else 
			//store it
		
	}
}