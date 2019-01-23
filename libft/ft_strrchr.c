/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 20:15:16 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/02 20:19:29 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *sp;

	sp = NULL;
	while (*s)
		if (*s++ == (char)c)
			sp = (char *)(s - 1);
	if (c == 0)
		return ((char *)s);
	return (sp);
}
