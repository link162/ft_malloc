/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:18:21 by ybuhai            #+#    #+#             */
/*   Updated: 2019/01/26 17:46:38 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		clear_gnl(t_gnl *new)
{
	t_gnl *t;

	while (new)
	{
		if (new->text)
			free(new->text);
		t = new->next;
		free(new);
		new = t;
	}
	exit(1);
}

static t_gnl	*ft_create_list(int fd)
{
	t_gnl *list;

	if (!(list = (t_gnl*)malloc(sizeof(*list))))
		return (NULL);
	list->fd = fd;
	list->tempo = ft_strnew(0);
	list->text = NULL;
	list->next = NULL;
	return (list);
}

static t_gnl	*ft_check_fd(t_gnl *save, int fd)
{
	t_gnl	*tmp;
	t_gnl	*d_list;
	t_gnl	*t;

	tmp = NULL;
	d_list = save;
	while (d_list)
	{
		if (d_list->fd == fd)
			return (d_list);
		if (!(d_list->next))
		{
			tmp = ft_create_list(fd);
			t = d_list;
			while (t->next)
				t = t->next;
			t->next = tmp;
			return (tmp);
		}
		d_list = d_list->next;
	}
	return (NULL);
}

static int		ft_check(char *save, char **line)
{
	char	*fin;

	if (!save)
		return (0);
	fin = ft_strchr(save, '\n');
	if (fin != NULL)
	{
		*fin = '\0';
		*line = ft_strdup(save);
		ft_strncpy(save, &fin[1], ft_strlen(&fin[1]) + 1);
		return (1);
	}
	else if (ft_strlen(save) > 0)
	{
		*line = ft_strdup(save);
		*save = '\0';
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_gnl	*save;
	t_gnl			*tmp;
	int				ret;

	if (fd == -5)
		clear_gnl(save);
	if (!(save))
		save = ft_create_list(fd);
	if (fd == -1 || line == NULL || BUFF_SIZE <= 0)
		return (-1);
	tmp = ft_check_fd(save, fd);
	while (!(ft_strchr(tmp->tempo, '\n')))
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		if (ret == 0)
			return (ft_check(tmp->text, line));
		buf[ret] = '\0';
		tmp->text = ft_strjoin(tmp->tempo, buf);
		free(tmp->tempo);
		tmp->tempo = tmp->text;
	}
	return (ft_check(tmp->text, line));
}
