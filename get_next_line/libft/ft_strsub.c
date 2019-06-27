/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 20:31:43 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/05 20:46:36 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*nstr;

	if (s == NULL)
		return (NULL);
	if (!(nstr = ft_strnew(len)))
		return (NULL);
	return (ft_strncpy(nstr, s + start, len));
}
