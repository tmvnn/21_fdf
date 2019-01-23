/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:50:21 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/04 00:07:05 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst,
		const void *src, int c, size_t n)
{
	unsigned char *dstp;
	unsigned char *srcp;

	dstp = (unsigned char *)dst;
	srcp = (unsigned char *)src;
	while (n)
	{
		*dstp = *srcp;
		if (*srcp == (unsigned char)c)
			return (dstp + 1);
		dstp++;
		srcp++;
		--n;
	}
	return (NULL);
}
