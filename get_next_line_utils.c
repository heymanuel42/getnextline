/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejanssen <ejanssen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:16:05 by ejanssen          #+#    #+#             */
/*   Updated: 2022/10/31 14:54:14 by ejanssen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*find_next_line(const char *buf, char c)
{
	while (*buf != '\0')
	{
		if (*buf == c)
			return ((char *)buf);
		buf++;
	}
	if (c == '\0')
		return ("\0");
	return (NULL);
}
