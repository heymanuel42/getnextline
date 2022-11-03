/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejanssen <ejanssen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:58:48 by ejanssen          #+#    #+#             */
/*   Updated: 2022/11/03 17:44:09 by ejanssen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize, size_t d_l);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_append(char *str, char *to_append);
char	*ft_readbuf(char *buf, ssize_t bread, char **overflow);
char	*get_next_line(int fd);
int		ft_find(const char *buf, ssize_t n_bytes, char c);
ssize_t	ft_readline(int fd, char *buf, char **overflow);
#endif