/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:10:22 by malde-ch          #+#    #+#             */
/*   Updated: 2024/10/17 10:11:22 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*free_join(char **s1, char *s2)
{
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	if (!*s1)
		*s1 = ft_strdup("");
	joined = ft_strjoin(*s1, s2);
	if (*s1)
		free(*s1);
	if (s2)
		free(s2);
	return (joined);
}

int	search_index(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '\n')
			return (1);
		(*i)++;
	}
	return (-1);
}

int	read_join(int fd, char **buff)
{
	int		bytes_read;
	char	*read_buffer;

	read_buffer = malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
		return (-1);
	bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(read_buffer);
		return (bytes_read);
	}
	read_buffer[bytes_read] = 0;
	*buff = free_join(buff, read_buffer);
	return (bytes_read);
}

char	*create_line(char **buff, int i)
{
	char	*line;
	char	*temp;

	line = ft_substr(*buff, 0, i + 1);
	temp = ft_substr(*buff, i + 1, ft_strlen(*buff) - i - 1);
	free(*buff);
	*buff = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buff[1024];
	int			i;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	if (!buff[fd])
		buff[fd] = ft_strdup("");
	while (1)
	{
		if (search_index(buff[fd], &i) >= 0)
			break ;
		if (read_join(fd, &buff[fd]) <= 0)
			break ;
	}
	if (!buff[fd][0])
	{
		free(buff[fd]);
		buff[fd] = NULL;
		return (NULL);
	}
	return (create_line(&buff[fd], i));
}
