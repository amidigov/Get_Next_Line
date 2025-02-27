/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amidigov <amidigov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 07:58:49 by amidigov          #+#    #+#             */
/*   Updated: 2024/12/05 16:31:31 by amidigov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	newline_check(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	newline_len(t_list *list)
{
	int	i;
	int	str_len;

	if (!list)
		return (0);
	str_len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				str_len++;
				return (str_len);
			}
			i++;
			str_len++;
		}
		list = list->next;
	}
	return (str_len);
}

void	lst_to_str(t_list *list, char *str)
{
	int	i;
	int	j;

	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			str[j] = list->content[i];
			j++;
			if (list->content[i] == '\n')
			{
				str[j] = '\0';
				return ;
			}
			i++;
		}
		list = list->next;
	}
	str[j] = '\0';
}

t_list	*list_last_node(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	free_list(t_list **list)
{
	t_list	*temp;

	while (*list)
	{
		temp = (*list)->next;
		free(*list);
		*list = temp;
	}
}
