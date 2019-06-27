/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:38:54 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/09 21:53:21 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_contdel(void *content, size_t content_size)
{
	free(content);
	content_size = 0;
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f) (t_list *elem))
{
	t_list		*new_l;
	t_list		*head_l;
	t_list		*old_l;

	head_l = NULL;
	if (lst && f)
	{
		if (!(new_l = ft_lstnew(lst->content, lst->content_size)))
			return (NULL);
		new_l = f(new_l);
		head_l = new_l;
		old_l = lst->next;
		while (old_l)
		{
			if (!(new_l->next = ft_lstnew(old_l->content, old_l->content_size)))
			{
				ft_lstdel(&head_l, ft_contdel);
				return (NULL);
			}
			new_l->next = f(new_l->next);
			new_l = new_l->next;
			old_l = old_l->next;
		}
	}
	return (head_l);
}
