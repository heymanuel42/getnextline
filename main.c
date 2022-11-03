/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejanssen <ejanssen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:01:10 by ejanssen          #+#    #+#             */
/*   Updated: 2022/11/03 18:00:56 by ejanssen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

void	ft_read(int fd)
{
	char	*c;

	c = get_next_line(fd);
	printf("%s", c);
	if (c)
		free(c);
}

int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	ft_read(fd);
	ft_read(fd);
	close(fd);
	return (0);
}
