/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amidigov <amidigov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 07:58:32 by amidigov          #+#    #+#             */
/*   Updated: 2024/12/07 13:47:54 by amidigov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	fill_buffer(t_list **list, char *buff)
{
	t_list	*last_node;
	int		i;
	int		j;

	last_node = list_last_node(*list);
	if (!last_node)
		return (-1);
	i = 0;
	j = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	if (last_node->content[i] == '\n')
		i++;
	while (last_node->content[i])
		buff[j++] = last_node->content[i++];
	buff[j] = '\0';
	return (0);
}

static char	*fill_line(t_list *list)
{
	char	*str;
	int		str_len;

	if (!list)
		return (NULL);
	str_len = newline_len(list);
	str = malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (NULL);
	lst_to_str(list, str);
	return (str);
}

static int	fill_list(t_list **list, char *buff)
{
	t_list	*new_node;
	t_list	*last_node;
	int		i;

	i = 0;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (-1);
	while (buff[i])
	{
		new_node->content[i] = buff[i];
		i++;
	}
	new_node->content[i] = '\0';
	new_node->next = NULL;
	if (*list == NULL)
		*list = new_node;
	else
	{
		last_node = list_last_node(*list);
		last_node->next = new_node;
	}
	return (0);
}

static int	make_list(t_list **list, char *buff, int fd)
{
	int		read_len;

	if (buff[0])
	{
		if (fill_list(list, buff) == -1)
			return (-1);
	}
	while (!newline_check(buff))
	{
		read_len = read(fd, buff, BUFFER_SIZE);
		if (read_len < 0)
			return (-1);
		if (read_len == 0)
			return (0);
		buff[read_len] = '\0';
		if (fill_list(list, buff) == -1)
			return (-1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	t_list		*list;

	list = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (make_list(&list, buff, fd) == -1)
	{
		free_list(&list);
		buff[0] = '\0';
		return (NULL);
	}
	line = fill_line(list);
	if (!line || fill_buffer(&list, buff) == -1)
	{
		free_list(&list);
		buff[0] = '\0';
		return (NULL);
	}
	free_list(&list);
	return (line);
}
