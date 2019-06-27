/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 17:52:59 by lbellona          #+#    #+#             */
/*   Updated: 2018/11/30 18:09:45 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *dstp;
	unsigned char *srcp;

	if (dst || src)
	{
		dstp = (unsigned char *)dst;
		srcp = (unsigned char *)src;
		if (dstp <= srcp || dstp >= srcp + len)
			while (len--)
				*dstp++ = *srcp++;
		else
		{
			dstp += len - 1;
			srcp += len - 1;
			while (len--)
				*dstp-- = *srcp--;
		}
	}
	return (dst);
}
