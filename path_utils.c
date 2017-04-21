/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 15:48:51 by atrudel           #+#    #+#             */
/*   Updated: 2017/03/23 16:25:44 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	delete_path(t_path **path)
{
	t_path	*to_delete;

	if (path)
	{
		while (*path)
		{
			to_delete = *path;
			*path = (*path)->next;
			free(to_delete);
		}
	}
}

t_path	*copy_path(t_path *path, t_data *data)
{
	t_path *node_copy;
	t_path *path_copy;
	t_path **tail;

	tail = &path_copy;
	while (path)
	{
		if (!(node_copy = (t_path *)malloc(sizeof(*node_copy))))
			error_exit("Malloc failed during path exploration", data);
		ft_bzero(node_copy, sizeof(*node_copy));
		node_copy->room = path->room;
		*tail = node_copy;
		tail = &node_copy->next;
		path = path->next;
	}
	return (path_copy);
}

void	set_path_lengths(t_list *paths)
{
	t_path	*current;
	int		length;

	while (paths)
	{
		current = (t_path *)paths->content;
		length = -1;
		while (current)
		{
			length++;
			current = current->next;
		}
		current = (t_path *)paths->content;
		while (current)
		{
			current->length = length;
			current->cost = length;
			current = current->next;
		}
		paths = paths->next;
	}
}

t_path	*get_path_end(t_path *path)
{
	while (path && path->next)
		path = path->next;
	return (path);
}

int		compare_paths(void *path1, void *path2)
{
	int length1;
	int length2;

	length1 = ((t_path *)path1)->length;
	length2 = ((t_path *)path2)->length;
	return (length1 - length2);
}
