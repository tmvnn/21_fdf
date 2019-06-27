/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 23:41:00 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/10 00:12:50 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	while (n--)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2++)
		{
			return ((unsigned char)*s1 - (unsigned char)*--s2);
		}
		if (*s1++ == 0)
			return (0);
	}
	return (0);
}
