/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejanssen <ejanssen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:59:57 by ejanssen          #+#    #+#             */
/*   Updated: 2022/11/03 14:18:39 by ejanssen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	ft_find(const char *buf, ssize_t n_bytes, char c)
{
	int	i;

	i = 0;
	while (i < n_bytes)
	{
		if (buf[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_append(char *str, char *to_append)
{
	char	*new;
	size_t	old_l;
	size_t	new_l;

	new_l = ft_strlen(to_append);
	if (str == NULL)
	{
		new = malloc(sizeof(char) * (new_l + 1));
		ft_strlcpy(new, to_append, new_l + 1);
		return (new);
	}
	old_l = ft_strlen(str);
	new = malloc(sizeof(char) * (old_l + new_l + 1));
	ft_strlcpy(new, str, old_l + 1);
	ft_strlcat(new, to_append, old_l + new_l + 1, old_l);
	free(str);
	free(to_append);
	return (new);
}

char	*ft_readbuf(char *buf, ssize_t bread, char **overflow)
{
	int		nl_i;
	char	*res;

	if (bread <= 0)
		return (NULL);
	res = NULL;
	nl_i = ft_find(buf, bread, '\n');
	if (nl_i >= 0)
	{
		res = ft_substr(buf, 0, nl_i + 1);
		if (*overflow)
			free(*overflow);
		*overflow = ft_substr(buf, nl_i + 1, bread - nl_i);
	}
	else
	{
		res = ft_strdup(buf);
		if (*overflow)
		{
			free(*overflow);
			*overflow = NULL;
		}
	}
	return (res);
}

ssize_t	ft_readline(int fd, char **buf, char **overflow)
{
	ssize_t	bread;

	if (*buf)
	{
		free(*buf);
		*buf = NULL;
	}
	if (*overflow)
	{
		*buf = ft_strdup(*overflow);
		bread = ft_strlen(*buf);
	}
	else
	{
		*buf = malloc(BUFFER_SIZE + 1);
		bread = read(fd, *buf, BUFFER_SIZE);
		if (bread <= 0)
		{
			free(*buf);
			*buf = NULL;
			return (bread);
		}
		(*buf)[bread] = '\0';
	}
	return (bread);
}

char	*get_next_line(int fd)
{
	static char	*overflow;
	char		*buf;
	ssize_t		bread;
	char		*res;

	buf = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bread = ft_readline(fd, &buf, &overflow);
	res = ft_readbuf(buf, bread, &overflow);
	if (bread == 0)
		return (NULL);
	while (ft_find(buf, bread, '\n') < 0 && bread > 0 && res != NULL)
	{
		bread = ft_readline(fd, &buf, &overflow);
		if (bread <= 0)
			break ;
		res = ft_append(res, ft_readbuf(buf, bread, &overflow));
	}
	if (buf)
		free(buf);
	return (res);
}
