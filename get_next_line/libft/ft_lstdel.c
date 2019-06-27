/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 18:57:51 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/09 19:50:16 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmplst;
	t_list	*nullst;

	if (alst && *alst)
	{
		nullst = *alst;
		while (*alst)
		{
			tmplst = *alst;
			*alst = tmplst->next;
			if (tmplst->content)
				del(tmplst->content, tmplst->content_size);
			free(tmplst);
		}
		nullst = NULL;
	}
}
