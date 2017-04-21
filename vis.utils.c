/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 16:08:28 by atrudel           #+#    #+#             */
/*   Updated: 2017/04/20 13:52:40 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

t_point	*set_point(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
	return (point);
}

void	get_stats(t_data *data)
{
	t_list	*current;

	if ((current = data->room_list))
	{
		data->x_max = ((t_room *)current->content)->x;
		data->x_min = ((t_room *)current->content)->x;
		data->y_max = ((t_room *)current->content)->y;
		data->y_min = ((t_room *)current->content)->y;
	}
	while (current)
	{
		if (((t_room *)current->content)->x > data->x_max)
			data->x_max = ((t_room *)current->content)->x;
		if (((t_room *)current->content)->x < data->x_min)
			data->x_min = ((t_room *)current->content)->x;
		if (((t_room *)current->content)->y > data->y_max)
			data->y_max = ((t_room *)current->content)->y;
		if (((t_room *)current->content)->y < data->y_min)
			data->y_min = ((t_room *)current->content)->y;
		current = current->next;
	}
}

void	normalize_coordinates(t_interface *inter)
{
	int		scale_x;
	int		scale_y;
	t_list	*current;
	t_room	*current_room;

	get_stats(inter->data);
	scale_x = (inter->size_x - 3 * ROOM_SIZE) /
		(inter->data->x_max - inter->data->x_min + 1);
	scale_y = (inter->size_y - 3 * ROOM_SIZE) /
		(inter->data->y_max - inter->data->y_min + 1);
	inter->data->middle_x = inter->data->x_min +
		(inter->data->x_max - inter->data->x_min) / 2;
	inter->data->middle_y = inter->data->y_min +
		(inter->data->y_max - inter->data->y_min) / 2;
	current = inter->data->room_list;
	while (current)
	{
		current_room = (t_room *)current->content;
		current_room->x = inter->size_x / 2 +
			(current_room->x - inter->data->middle_x) * scale_x;
		current_room->y = inter->size_y / 2 +
			(current_room->y - inter->data->middle_y) * scale_y;
		current = current->next;
	}
}

int		get_ant_color(int ant_nb)
{
	static int colors[12] = {
		0xFF0000,
		0xFF8000,
		0xFFFF00,
		0x40FF00,
		0x00FFFF,
		0x0080FF,
		0xFF00FF,
		0xFFA07A,
		0xFF8C00,
		0x008000,
		0x20B2AA,
		0x8B4513,
	};

	ant_nb = ant_nb % 12;
	return (colors[ant_nb]);
}
