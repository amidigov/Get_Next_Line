/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amidigov <amidigov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:07:03 by amidigov          #+#    #+#             */
/*   Updated: 2024/12/07 15:09:38 by amidigov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			content[BUFFER_SIZE + 1];
	struct s_list	*next;
}					t_list;
char	*get_next_line(int fd);
void	free_list(t_list **list);
t_list	*list_last_node(t_list *list);
int		newline_len(t_list *list);
int		newline_check(char *buf);
void	lst_to_str(t_list *list, char *str);
#endif