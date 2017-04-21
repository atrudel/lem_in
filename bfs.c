/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 12:52:27 by atrudel           #+#    #+#             */
/*   Updated: 2017/04/20 11:26:01 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	delete_overlapping_paths(t_data *data, t_path *reference,
		t_list *to_spare)
{
	t_list	*current;
	t_list	*next;

	current = data->paths;
	while (current)
	{
		next = current->next;
		if (paths_overlap((t_path *)current->content, reference))
		{
			set_as_unvisited((t_path *)current->content);
			delete_path((t_path **)&(current->content));
			if (current != to_spare)
				ft_lstremove(&data->paths, current, NULL);
		}
		current = next;
	}
}

void	advance_path(t_list *path, t_data *data)
{
	t_list	*connection;
	t_path	*new_path;

	connection = get_path_end((t_path *)path->content)->room->connections;
	while (connection)
	{
		if (((t_room *)connection->content)->end)
		{
			new_path = copy_path((t_path *)path->content, data);
			extend_path(&new_path, (t_room *)(connection->content), data);
			delete_overlapping_paths(data, new_path, path);
			set_as_visited(new_path);
			extend_lst_beginning(&data->paths, new_path, data);
			return ;
		}
		else if (!((t_room *)connection->content)->visited)
		{
			((t_room *)connection->content)->visited = 1;
			new_path = copy_path((t_path *)path->content, data);
			extend_path(&new_path, (t_room *)connection->content, data);
			extend_lst(&data->paths, new_path, data);
		}
		connection = connection->next;
	}
	delete_path((t_path **)&path->content);
}

void	bfs(t_data *data)
{
	t_path	*starting_path;
	t_list	*current;
	t_list	*next;

	starting_path = NULL;
	extend_path(&starting_path, data->start, data);
	data->start->visited = 1;
	extend_lst(&data->paths, (void *)starting_path, data);
	current = data->paths;
	while (current)
	{
		advance_path(current, data);
		next = current->next;
		ft_lstremove(&data->paths, current, lst_delete_path);
		current = next;
	}
	set_path_lengths(data->paths);
	ft_lstsort(data->paths, compare_paths);
	if (ft_lstsize(data->paths) == 0)
	{
		ft_asprintf(&data->error_fb, "No path could be found\n");
		error_exit("ERROR", data);
	}
}
