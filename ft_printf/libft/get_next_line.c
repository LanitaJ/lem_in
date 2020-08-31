/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerk <ljerk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:50:59 by ljerk             #+#    #+#             */
/*   Updated: 2020/08/19 17:27:46 by ljerk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	out(char **line, char *ostatok)
{
	char	*sn;

	sn = ft_strchr(ostatok, '\n');
	if (sn)
	{
		*sn = '\0';
		sn++;
		*line = ft_strdup(ostatok);
		ft_memmove(ostatok, sn, ft_strlen(sn) + 1);
		return (1);
	}
	else if (ft_strlen(ostatok) > 0)
	{
		*line = ft_strdup(ostatok);
		*ostatok = 0;
		return (1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	int				oput;
	int				size;
	char			buf[BUFF_SIZE + 1];
	static char		*ostatok[10240];
	char			*tmp;

	if (fd < 0 || fd > 10240 || BUFF_SIZE < 1 || !line)
		return (-1);
	if (!ostatok[fd] && !(ostatok[fd] = ft_strnew(1)))
		return (-1);
	while (!(ft_strchr(ostatok[fd], '\n')))
	{
		if ((size = read(fd, buf, BUFF_SIZE)) == -1)
			return (-1);
		if (size == 0)
			break ;
		buf[size] = '\0';
		tmp = ostatok[fd];
		ostatok[fd] = ft_strjoin(ostatok[fd], buf);
		free(tmp);
	}
	oput = out(line, ostatok[fd]);
	return (oput);
}
