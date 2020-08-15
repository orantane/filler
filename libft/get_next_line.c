/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 02:26:01 by orantane          #+#    #+#             */
/*   Updated: 2020/08/15 19:54:38 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_copy(char **line, const int fd, char **strings)
{
	int		i;
	char	*rest;

	i = 0;
	while (strings[fd][i] != '\n' && strings[fd][i] != '\0')
		i++;
	if (strings[fd][i] == '\n')
	{
		*line = ft_strsub(strings[fd], 0, i);
		rest = ft_strdup(&strings[fd][i + 1]);
		free(strings[fd]);
		strings[fd] = rest;
		if (strings[fd][0] == '\0')
			ft_strdel(&strings[fd]);
	}
	else
	{
		*line = ft_strdup(strings[fd]);
		ft_strdel(&strings[fd]);
	}
	return (1);
}

static int	checkout(char **line, const int fd, char **strings, int ret)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && strings[fd] == NULL)
		return (0);
	else
		return (ft_copy(line, fd, strings));
}

int			get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	static char	*strings[FD_SIZE];
	char		*temp;
	int			ret;

	if (fd < 0 || !line || fd > FD_SIZE)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (strings[fd] == NULL)
			strings[fd] = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(strings[fd], buff);
			free(strings[fd]);
			strings[fd] = temp;
		}
		if (ft_strchr(strings[fd], '\n'))
			break ;
	}
	return (checkout(line, fd, strings, ret));
}
