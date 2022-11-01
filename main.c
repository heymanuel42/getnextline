/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejanssen <ejanssen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:01:10 by ejanssen          #+#    #+#             */
/*   Updated: 2022/11/01 12:35:48 by ejanssen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	char *c = get_next_line(fd);
	printf("%s", c);
	if (c)
		free(c);
	c = get_next_line(fd);
	printf("%s", c);
	if (c)
		free(c);
	c = get_next_line(fd);
	printf("%s", c);
	if (c)
		free(c);
	c = get_next_line(fd);
	printf("%s", c);
	if (c)
		free(c);
	close(fd);
	return (0);
}
