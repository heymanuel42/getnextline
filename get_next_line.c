/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejanssen <ejanssen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:59:57 by ejanssen          #+#    #+#             */
/*   Updated: 2022/10/31 15:14:17 by ejanssen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}

char	*get_next_line(int fd)
{
	char	buf[BUFFER_SIZE];
	char	*res;
	int		i;
	ssize_t	bytes_read;

	i = 0;
	bytes_read = read(fd, buf, BUFFER_SIZE);
	printf("%s", buf);
	while (bytes_read == BUFFER_SIZE && !find_next_line(buf, '\n'))
	{
		printf("%s", buf);
		if (find_next_line(buf, '\n'))
		{
			printf("\n");
			return (NULL);
		}
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	return (NULL);
}
