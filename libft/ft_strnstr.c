/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 21:14:40 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/02 22:05:21 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		si;
	size_t		fi;
	const char	*p_end;

	si = 0;
	if (!haystack[0] && !needle[0])
		return ((char *)haystack);
	p_end = haystack + len;
	while (haystack[si] && (&haystack[si] < p_end))
	{
		fi = 0;
		if (needle[fi] == '\0')
			return ((char *)haystack);
		while (needle[fi] == haystack[si + fi] && (&haystack[si + fi] < p_end))
		{
			if (needle[fi + 1] == '\0')
				return ((char *)(haystack + si));
			fi++;
		}
		si++;
	}
	return ((char *)0);
}
