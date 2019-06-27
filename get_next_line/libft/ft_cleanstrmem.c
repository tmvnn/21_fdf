/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanstrmem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 00:17:52 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/10 00:21:19 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_cleanstrmem(char **s)
{
	char **sp;

	sp = s;
	while (*sp)
		ft_strdel(sp++);
	ft_strdel(s);
	return (NULL);
}
