/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohsawa <yohsawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:00:11 by yohsawa           #+#    #+#             */
/*   Updated: 2026/05/30 15:02:47 by yohsawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_gnl(char *line, char *buf)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!line)
		line = ft_strdup("");
	if (!line || !buf)
		return (free(line), NULL);
	str = malloc(ft_strlen(line) + ft_strlen(buf) + 1);
	if (!str)
		return (free(line), NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		str[i] = line[i];
		i++;
	}
	while (buf[j])
		str[i++] = buf[j++];
	str[i] = '\0';
	free(line);
	return (str);
}
