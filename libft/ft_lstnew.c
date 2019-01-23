/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 16:47:34 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/09 17:47:02 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *newlst;

	if ((newlst = (t_list*)malloc(sizeof(t_list))))
	{
		if (content)
		{
			if (!(newlst->content = ft_memalloc(content_size)))
			{
				free(newlst);
				return (NULL);
			}
			ft_memcpy(newlst->content, content, content_size);
			newlst->content_size = content_size;
		}
		else
		{
			newlst->content = NULL;
			newlst->content_size = 0;
		}
		newlst->next = NULL;
	}
	return (newlst);
}
