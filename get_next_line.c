/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <lbellona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 18:12:32 by lbellona          #+#    #+#             */
/*   Updated: 2019/09/29 17:47:59 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static t_list		*get_file(t_list **files, int fd)
{
	t_list			*tmp_l;

	tmp_l = *files;
	while (tmp_l)
	{
		if (fd == (int)tmp_l->content_size)
			return (tmp_l);
		tmp_l = tmp_l->next;
	}
	if (!(tmp_l = ft_lstnew(NULL, 0)))
		return (NULL);
	tmp_l->content = ft_strdup("\0");
	tmp_l->content_size = fd;
	ft_lstadd(files, tmp_l);
	return (*files);
}

static int			fr_n_re(char **oldstr, char *newstr)
{
	char			*tmp;

	tmp = *oldstr;
	if (!newstr)
		return (0);
	*oldstr = newstr;
	free(tmp);
	return (1);
}

static int			read_line(char **line, char **content)
{
	char			*nl_pos;

	if ((nl_pos = ft_strchr(*content, '\n')))
	{
		*nl_pos = '\0';
		SF_ALCN((fr_n_re(line, ft_strjoin(*line, *content))));
		SF_ALCN((fr_n_re(content, ft_strdup(nl_pos + 1))));
		return (1);
	}
	SF_ALCN((fr_n_re(line, ft_strjoin(*line, *content))));
	SF_ALCN((fr_n_re(content, ft_strdup(*content + ft_strlen(*content)))));
	return (2);
}

int					get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	int				read_s;
	int				ret_value;
	static t_list	*files;
	t_list			*cur_f;

	if (fd < 0 || !line || read(fd, buff, 0) < 0)
		return (-1);
	SF_ALCN((*line = (char *)malloc(sizeof(char))));
	SF_ALCN((cur_f = get_file(&files, fd)));
	**line = 0;
	ret_value = 0;
	if (*(char*)(cur_f->content))
		if ((ret_value = read_line(line, (char **)&cur_f->content)) < 2)
			return (ret_value);
	while ((read_s = read(fd, buff, BUFF_SIZE)))
	{
		buff[read_s] = '\0';
		SF_ALCN((fr_n_re((char **)&cur_f->content,
						ft_strjoin(cur_f->content, buff))));
		if ((ret_value = read_line(line, (char **)&cur_f->content)) < 2)
			return (ret_value);
	}
	return (ret_value > 0 ? 1 : 0);
}
