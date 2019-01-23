/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 00:02:08 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/11 19:00:38 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t dlen;
	size_t slen;

	i = 0;
	dlen = ft_strlen((char*)dst);
	slen = ft_strlen((char*)src);
	if (dstsize <= dlen)
		return (slen + dstsize);
	while (dst[i] && i < dstsize - 1)
		i++;
	while (*src && i < dstsize - 1)
		dst[i++] = *src++;
	dst[i] = '\0';
	return (dlen + slen);
}
