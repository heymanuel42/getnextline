/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejanssen <ejanssen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:59:57 by ejanssen          #+#    #+#             */
/*   Updated: 2022/11/01 12:45:55 by ejanssen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	find_next_line(const char *buf, char c)
{
	int	i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

char	*append(char *str, char *to_append)
{
	char	*new;
	size_t	old_l;

	if (str == NULL)
	{
		new = malloc(sizeof(char) * (ft_strlen(to_append) + 1));
		ft_strlcat(new, to_append, ft_strlen(to_append) + 1);
		return (new);
	}
	old_l = ft_strlen(str);
	new = malloc(sizeof(char) * (old_l + ft_strlen(to_append) + 1));
	ft_strlcpy(new, str, ft_strlen(str) + 1);
	ft_strlcat(new, to_append, old_l + ft_strlen(to_append) + 1);
	free(str);
	return (new);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE];
	static char	*backup;
	char		*curr;
	ssize_t		bytes_read;

	if (fd < 0)
		return (NULL);
	if (backup == NULL)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if(bytes_read == 0)
			return (NULL);
		curr = ft_strdup(buf);
	}
	else
	{
		curr = ft_strdup(backup);
	}
	if (find_next_line(curr, '\n') >= 0)
	{
		backup = ft_substr(curr, find_next_line(curr, '\n') + 1, ft_strlen(curr));
		curr = ft_substr(curr, 0, find_next_line(curr, '\n') + 1);
		return (curr);
	}
	else
	{
		while (find_next_line(curr, '\n') < 0)
		{
			bytes_read = read(fd, buf, BUFFER_SIZE);
			if (find_next_line(buf, '\n') >= 0)
			{
				curr = append(curr, ft_substr(buf, 0, find_next_line(buf, '\n') + 1));
				if(find_next_line(buf, '\0') >= 0)
				{
					free(backup);
					backup = NULL;
				}
				else
					backup = ft_substr(buf, find_next_line(buf, '\n') + 1, ft_strlen(buf));
			}
			else
			{
				curr = append(curr, buf);
			}
		}
	}
	return (curr);
}
