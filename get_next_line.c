/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jphilip- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 20:23:34 by jphilip-          #+#    #+#             */
/*   Updated: 2019/01/17 20:16:44 by jphilip-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	t_list	*ft_getlist(t_list **list, int fd)
{
	t_list				*tmp;

	tmp = *list;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("", fd);
	ft_lstadd(list, tmp);
	return (tmp);
}

static void		ft_getline(char **line, t_list *tmp)
{
	int		n;
	char	*str;

	n = 0;
	while (((char *)(tmp->content))[n] != '\n' &&
			((char *)(tmp->content))[n] != '\0')
		n++;
	*line = ft_strsub(tmp->content, 0, n);
	if (n < (int)ft_strlen(tmp->content))
	{
		str = ft_strdup(tmp->content + n + 1);
		free(tmp->content);
		tmp->content = str;
	}
	else
		ft_memdel(tmp->content);
}

int				get_next_line(const int fd, char **line)
{
	char			c[BUFF_SIZE + 1];
	int				n;
	static t_list	*list;
	t_list			*tmp;
	char			*str;

	if (fd < 0 || line == NULL || read(fd, c, 0) < 0)
		return (-1);
	tmp = ft_getlist(&list, fd);
	while ((n = read(fd, c, BUFF_SIZE)))
	{
		c[n] = '\0';
		if (tmp->content == NULL)
			tmp->content = ft_strnew(1);
		str = ft_strjoin(tmp->content, c);
		free(tmp->content);
		tmp->content = str;
		if (ft_strchr(c, '\n'))
			break ;
	}
	if (n < BUFF_SIZE && !ft_strlen(tmp->content))
		return (0);
	ft_getline(line, tmp);
	return (1);
}
