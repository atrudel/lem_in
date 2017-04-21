/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 18:11:50 by atrudel           #+#    #+#             */
/*   Updated: 2017/04/20 13:49:40 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		paths_overlap(t_path *path1, t_path *path2)
{
	t_path	*cursor1;
	t_path	*cursor2;

	cursor1 = path1;
	while (cursor1)
	{
		cursor2 = path2;
		while (cursor2)
		{
			if (cursor1->room == cursor2->room && !cursor1->room->end &&
				!cursor1->room->start)
				return (1);
			cursor2 = cursor2->next;
		}
		cursor1 = cursor1->next;
	}
	return (0);
}

void	set_as_visited(t_path *path)
{
	while (path)
	{
		path->room->visited = 1;
		path = path->next;
	}
}

void	set_as_unvisited(t_path *path)
{
	while (path)
	{
		path->room->visited = 0;
		path = path->next;
	}
}

void	extend_path(t_path **path, t_room *position, t_data *data)
{
	t_path	*new_path_node;

	while (*path)
		path = &(*path)->next;
	if (!(new_path_node = (t_path *)malloc(sizeof(t_path))))
		error_exit("Malloc failed during path creation", data);
	ft_bzero(new_path_node, sizeof(*new_path_node));
	new_path_node->room = position;
	*path = new_path_node;
}
