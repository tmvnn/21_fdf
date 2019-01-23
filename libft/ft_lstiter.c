/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:26:49 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/09 20:38:12 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*tmplst;

	if (lst && f)
	{
		tmplst = lst;
		while (tmplst)
		{
			f(tmplst);
			tmplst = tmplst->next;
		}
	}
}
