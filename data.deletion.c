/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.deletion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:48:34 by atrudel           #+#    #+#             */
/*   Updated: 2017/03/23 16:08:50 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	lst_delete_room(void *content, size_t size)
{
	t_room *room;

	(void)size;
	room = (t_room *)content;
	ft_strdel(&room->label);
	ft_lstdel(&room->connections, NULL);
	free(room);
}

void	lst_delete_path(void *content, size_t size)
{
	t_path	*current;
	t_path	*next;

	(void)size;
	current = (t_path *)content;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	lst_delete_ant(void *content, size_t size)
{
	t_ant *ant;

	(void)size;
	ant = (t_ant *)content;
	ft_strdel(&ant->label);
	free(ant);
}

void	delete_data(t_data *data)
{
	ft_lstdel(&data->room_list, lst_delete_room);
	ft_lstdel(&data->input, lst_free_content);
	ft_lstdel(&data->paths, lst_delete_path);
	ft_lstdel(&data->lst_ants, lst_delete_ant);
	ft_strdel(&data->error_fb);
}
