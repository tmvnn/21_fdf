/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 19:03:18 by lbellona          #+#    #+#             */
/*   Updated: 2018/11/30 20:19:03 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *s1p;
	const unsigned char *s2p;

	s1p = (const unsigned char *)s1;
	s2p = (const unsigned char *)s2;
	if (n != 0)
	{
		while (--n && (*s1p == *s2p))
		{
			s1p++;
			s2p++;
		}
		return (*s1p - *s2p);
	}
	return (0);
}
