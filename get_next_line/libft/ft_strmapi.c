/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 19:59:00 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/05 20:05:29 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret;
	char			*rb;
	unsigned int	ind;

	if (!s || !f)
		return (NULL);
	if (!(ret = (char*)malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (NULL);
	rb = ret;
	ind = 0;
	while (*s)
		*ret++ = f(ind++, *s++);
	*ret = 0;
	return (rb);
}
