/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 18:17:20 by ybuhai            #+#    #+#             */
/*   Updated: 2018/11/07 12:41:25 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tmp;
	t_list *res;

	if (!lst)
		return (NULL);
	tmp = f(lst);
	res = tmp;
	while (lst->next)
	{
		lst = lst->next;
		tmp->next = f(lst);
		if (!tmp->next)
		{
			free(tmp->next);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (res);
}
