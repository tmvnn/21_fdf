/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 22:31:13 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/07 22:40:19 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t st_c;
	size_t end_c;

	if (!s)
		return (NULL);
	st_c = 0;
	while (s[st_c] && (s[st_c] == '\n' || s[st_c] == '\t' || s[st_c] == ' '))
		st_c++;
	end_c = ft_strlen(s) - 1;
	while (end_c > st_c && (s[end_c] == '\n' ||
				s[end_c] == '\t' || s[end_c] == ' '))
		end_c--;
	return (ft_strsub(s, st_c, end_c - st_c + 1));
}
