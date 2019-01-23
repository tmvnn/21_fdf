/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 20:23:42 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/02 21:13:51 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t si;
	size_t fi;

	si = 0;
	if (!haystack[0] && !needle[0])
		return ((char *)haystack);
	while (haystack[si])
	{
		fi = 0;
		if (needle[fi] == '\0')
			return ((char *)haystack);
		while (needle[fi] == haystack[si + fi])
		{
			if (needle[fi + 1] == '\0')
				return ((char *)(haystack + si));
			fi++;
		}
		si++;
	}
	return ((char *)0);
}
