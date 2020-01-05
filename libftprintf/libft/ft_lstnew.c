/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:48:31 by ybuhai            #+#    #+#             */
/*   Updated: 2018/11/10 13:36:59 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *begin;

	begin = (t_list *)malloc(sizeof(t_list));
	if (!begin)
		return (NULL);
	if (!content)
	{
		begin->content_size = 0;
		begin->content = NULL;
	}
	else
	{
		begin->content = malloc(content_size);
		if (!begin->content)
			return (NULL);
		ft_memcpy(begin->content, content, content_size);
		begin->content_size = content_size;
	}
	begin->next = NULL;
	return (begin);
}
