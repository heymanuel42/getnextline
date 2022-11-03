/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejanssen <ejanssen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:01:10 by ejanssen          #+#    #+#             */
/*   Updated: 2022/11/03 14:12:28 by ejanssen         ###   ########.fr       */
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
	//printf("%s", c);
	if (c)
		free(c);
}

int	main(void)
{
	int	fd;

	fd = open("empty.txt", O_RDONLY);
	ft_read(fd);
	close(fd);
	printf("%d\n",cnt);
	//while(1);
	return (0);
}
