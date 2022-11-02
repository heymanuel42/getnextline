/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejanssen <ejanssen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:59:57 by ejanssen          #+#    #+#             */
/*   Updated: 2022/11/02 09:47:10 by ejanssen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	find(const char *buf, ssize_t n_bytes, char c)
{
	int	i;

	i = 0;
	while (i < n_bytes)
	{
		if (buf[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (-2);
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

char	*read_until_next_line(int fd, char **overflow)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	bread;
	int		i;
	char	*res;

	if (*overflow)
	{
		ft_strlcpy(buf, *overflow, ft_strlen(*overflow) + 1);
		bread = ft_strlen(buf);

	}
	else
	{
		bread = read(fd, buf, BUFFER_SIZE);
		buf[bread] = '\0';
	}
	if (bread <= 0)
		return (NULL);
	res = NULL;
	if (find(buf, bread, '\n') >= 0)
	{
		res = append(res, ft_substr(buf, 0, find(buf, bread, '\n') + 1));
		*overflow = ft_substr(
				buf,
				find(buf, bread, '\n') + 1,
				bread - find(buf, bread, '\n'));
		return (res);
	}
	else
	{
		res = append(res, buf);
	}
	i = 0;
	while (find(buf, bread, '\n') < 0 && bread > 0)
	{
		if (*overflow)
		{
			ft_strlcpy(buf, *overflow, ft_strlen(*overflow) + 1);
			bread = ft_strlen(buf);
		}
		else
		{
			bread = read(fd, buf, BUFFER_SIZE);
			buf[bread] = '\0';
		}
		if (find(buf, bread, '\n') >= 0)
		{
			res = append(res, ft_substr(buf, 0, find(buf, bread, '\n') + 1));
			*overflow = ft_strdup(buf + find(buf, bread, '\n') + 1);
			return (res);
		}
		else if (bread != BUFFER_SIZE)
		{
			res = append(res, buf);
			return (res);
		}
		else
		{
			res = append(res, buf);
		}
		i++;
	}
	return (res);
}

char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	char		*tmp;
	static char	*overflow;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = read_until_next_line(fd, &overflow);
	if (!tmp)
		return (NULL);
	return (tmp);
}
