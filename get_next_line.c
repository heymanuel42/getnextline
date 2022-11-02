/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejanssen <ejanssen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:59:57 by ejanssen          #+#    #+#             */
/*   Updated: 2022/11/02 11:59:33 by ejanssen         ###   ########.fr       */
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
	if (c == '\0')
		return (-2);
	return (-1);
}

char	*ft_append(char *str, char *to_append)
{
	char	*new;
	size_t	old_l;

	if (str == NULL)
	{
		new = malloc(sizeof(char) * (ft_strlen(to_append) + 1));
		ft_strlcpy(new, to_append, ft_strlen(to_append) + 1);
		return (new);
	}
	old_l = ft_strlen(str);
	new = malloc(sizeof(char) * (old_l + ft_strlen(to_append) + 1));
	ft_strlcpy(new, str, ft_strlen(str) + 1);
	ft_strlcat(new, to_append, old_l + ft_strlen(to_append) + 1);
	free(str);
	return (new);
}

char	*ft_getline(char *buf, ssize_t bread, char **overflow)
{
	int		nl_i;
	char	*res;

	res = NULL;
	nl_i = ft_find(buf, bread, '\n');
	if (nl_i >= 0)
	{
		res = ft_substr(buf, 0, nl_i + 1);
		if(*overflow)
			free(*overflow);
		*overflow = ft_substr(buf, nl_i + 1, bread - nl_i);
		//printf("$%s$\n", *overflow);
		if (ft_strlen(*overflow) == 0)
		{
			free(*overflow);
			*overflow = NULL;
		}
	}
	else if (bread != BUFFER_SIZE)
	{
		res = ft_strdup(buf);
		if (*overflow)
		{
			free(*overflow);
			*overflow = NULL;
		}
	}
	else
	{
		res = ft_strdup(buf);
	}
	return (res);
}

char	*read_until_next_line(int fd, char **overflow)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	bread;
	char	*res;
	char	*tmp;
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
	res = ft_getline(buf, bread, overflow);
	while (ft_find(buf, bread, '\n') < 0 && bread > 0)
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
		if (bread <= 0)
			break;
		//printf("buff=%s res=%s line=%s\n", buf, res, get_line(buf, bread, overflow));
		tmp = ft_getline(buf, bread, overflow);
		res = ft_append(res, tmp);
		if(tmp)
			free(tmp);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	char		*tmp;
	static char	*overflow;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = read_until_next_line(fd, &overflow);
	if (!tmp)
		return (NULL);
	return (tmp);
}
