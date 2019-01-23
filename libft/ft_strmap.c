/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 19:22:51 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/05 19:54:31 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*ret;
	char	*rb;

	if (!s || !f)
		return (NULL);
	if (!(ret = (char*)malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (NULL);
	rb = ret;
	while (*s)
		*ret++ = f(*s++);
	*ret = 0;
	return (rb);
}
