/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 22:25:02 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/04 00:06:40 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *dstp;
	unsigned char *srcp;

	if (dst || src)
	{
		dstp = (unsigned char *)dst;
		srcp = (unsigned char *)src;
		while (n)
		{
			*dstp++ = *srcp++;
			--n;
		}
	}
	return (dst);
}
