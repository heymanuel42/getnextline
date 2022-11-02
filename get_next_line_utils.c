/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejanssen <ejanssen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:16:05 by ejanssen          #+#    #+#             */
/*   Updated: 2022/11/02 15:15:41 by ejanssen         ###   ########.fr       */
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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	const char	*start;

	start = src;
	if (dstsize > 0)
	{
		while (dstsize - 1 > 0 && *src)
		{
			*dst++ = *src++;
			dstsize--;
		}
	}
	while (*src++)
		;
	if (dstsize > 0)
		*dst = '\0';
	return (src - start - 1);
}

char	*ft_strdup(const char *src)
{
	char	*cpy;
	int		i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src) + 1;
	cpy = malloc(src_len);
	while (src[i] != '\0')
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int		src_id;
	size_t	dst_len;
	size_t	src_len;
	size_t	offset;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	offset = dst_len;
	src_id = 0;
	if (dstsize == 0)
		return (src_len);
	while (src[src_id] != '\0' && offset < dstsize - 1)
	{
		dst[offset] = src[src_id];
		offset++;
		src_id++;
	}
	dst[dst_len + src_id] = '\0';
	if (dstsize < dst_len)
		return (src_len + dstsize);
	return (dst_len + src_len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	char	*begin;
	size_t	i;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen((s + start));
	sub = malloc((len + 1) * sizeof (char));
	if (sub == NULL)
		return (NULL);
	begin = sub;
	i = 0;
	while (i < len && (i + start) < ft_strlen(s))
	{
		*(sub++) = s[i + start];
		i++;
	}
	*sub = '\0';
	if (len == 0)
	{
		free(begin);
		begin = NULL;
	}
	return ((char *)begin);
}
