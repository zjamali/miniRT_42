/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 22:26:31 by zjamali           #+#    #+#             */
/*   Updated: 2019/12/17 15:30:39 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		delete_node(t_list **head, int fd)
{
	t_list	*temp;
	t_list	*prev;

	temp = *head;
	if (temp != NULL && temp->fd == fd)
	{
		*head = temp->next;
		free(temp);
		temp = NULL;
		return ;
	}
	while (temp != NULL && temp->fd != fd)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free(temp);
	temp = NULL;
}

static t_list	*lstnew(int fd)
{
	t_list *lst;

	if (!(lst = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	lst->fd = fd;
	lst->next = NULL;
	lst->str = NULL;
	return (lst);
}

static t_list	*check(t_list **lst, int fd)
{
	t_list	*ptr;

	if (*lst == NULL)
	{
		(*lst) = lstnew(fd);
		return (*lst);
	}
	ptr = *lst;
	if (ptr->fd == fd)
	{
		return (ptr);
	}
	while (ptr->next != NULL)
	{
		if (ptr->next->fd == fd)
		{
			return (ptr->next);
		}
		ptr = ptr->next;
	}
	ptr->next = lstnew(fd);
	return (ptr->next);
}

static int		get_line(t_list *lst, char **line, int n, t_list **head)
{
	char	*temp;
	int		i;

	i = 0;
	if (!lst->str)
		lst->str = ft_strdup("");
	temp = lst->str;
	while (lst->str[i] != '\n' && lst->str[i] != '\0')
		i++;
	*line = ft_substr(lst->str, 0, i);
	if (lst->str[i] == '\0' && n == 0)
	{
		delete_node(head, lst->fd);
		free(temp);
		temp = NULL;
		return (0);
	}
	else
		lst->str = ft_strdup(lst->str + i + 1);
	free(temp);
	if (!lst->str || !*line)
		return (-1);
	if (n || (n == 0 && lst->str != NULL))
		return (1);
	return (-1);
}

int				get_next_line(int fd, char **line)
{
	int				n;
	char			*buff;
	static t_list	*head;
	t_list			*lst;
	char			*temp;

	lst = check(&head, fd);
	if (ft_strchr(lst->str, '\n'))
		return (get_line(lst, line, 1, &head));
	if (fd < 0 || fd > 4682 || (buff = (char*)malloc(BUFFER_SIZE + 1)) == NULL \
			|| read(fd, buff, 0) || line == NULL || BUFFER_SIZE < 0)
		return (-1);
	while (!ft_strchr(lst->str, '\n') && (n = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[n] = '\0';
		temp = lst->str;
		if (lst->str == NULL)
			lst->str = ft_strdup(buff);
		else
			lst->str = ft_strjoin(lst->str, buff);
		free(temp);
	}
	free(buff);
	return (get_line(lst, line, n, &head));
}
