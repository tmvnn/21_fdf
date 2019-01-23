/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabscl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 20:00:43 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/10 20:00:48 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtabscl(char *src)
{
	int		i;
	int		len;
	char	*dupstr;

	i = -1;
	len = 0;
	while (src[++i] != '\0')
		if (src[i] != 32 && (src[i] < 8 || src[i] > 13))
			len++;
	dupstr = (char*)malloc(len * sizeof(char) + 1);
	if (dupstr == 0)
		return (0);
	i = -1;
	len = -1;
	while (src[++i] != '\0')
		if (src[i] != 32 && (src[i] < 8 || src[i] > 13))
			dupstr[++len] = src[i];
	dupstr[len + 1] = '\0';
	return (dupstr);
}
