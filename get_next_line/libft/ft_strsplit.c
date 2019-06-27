/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 22:33:15 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/10 00:19:57 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_arr_alloc(char const *s, char c)
{
	char		**ret;
	size_t		i;
	size_t		w_size;

	if (!(ret = (char**)malloc(sizeof(char*) * (ft_word_count(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			w_size = 0;
			while (*s != c && *s)
			{
				w_size++;
				s++;
			}
			if (!(ret[i] = ft_strnew(w_size)))
				return (ft_cleanstrmem(ret));
			ft_strncpy(ret[i++], --s - w_size + 1, w_size);
		}
		s++;
	}
	ret[i] = 0;
	return (ret);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**ret;

	if (!s)
		return (NULL);
	ret = ft_arr_alloc(s, c);
	return (ret);
}
