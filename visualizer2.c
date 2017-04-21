/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 10:18:07 by atrudel           #+#    #+#             */
/*   Updated: 2017/04/21 10:23:59 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	draw_room(t_interface *inter, t_room *room)
{
	t_point point1;
	t_point point2;
	int		color;

	if (room->start)
		color = 0x0000FF00;
	else if (room->end)
		color = 0x00FF0000;
	else
		color = 0x00FFFFFF;
	set_point(&point1, room->x, room->y);
	set_point(&point2, room->x + ROOM_SIZE, room->y);
	draw_line(inter, &point1, &point2, color);
	set_point(&point1, room->x, room->y);
	set_point(&point2, room->x, room->y + ROOM_SIZE);
	draw_line(inter, &point1, &point2, color);
	set_point(&point1, room->x + ROOM_SIZE, room->y);
	set_point(&point2, room->x + ROOM_SIZE, room->y + ROOM_SIZE);
	draw_line(inter, &point1, &point2, color);
	set_point(&point1, room->x, room->y + ROOM_SIZE);
	set_point(&point2, room->x + ROOM_SIZE, room->y + ROOM_SIZE);
	draw_line(inter, &point1, &point2, color);
}

static void	draw_tube(t_interface *inter, t_room *room1, t_room *room2)
{
	t_point	point1;
	t_point	point2;
	int		color;

	color = 0x00FFFFFF;
	set_point(&point1, room1->x + ROOM_SIZE / 2, room1->y + ROOM_SIZE / 2);
	set_point(&point2, room2->x + ROOM_SIZE / 2, room2->y + ROOM_SIZE / 2);
	draw_line(inter, &point1, &point2, color);
}

void		draw_antheap(t_interface *inter)
{
	t_list		*room_lst;
	t_room		*current_room;
	t_list		*connection_lst;

	room_lst = inter->data->room_list;
	while (room_lst)
	{
		current_room = (t_room *)room_lst->content;
		connection_lst = current_room->connections;
		while (connection_lst)
		{
			draw_tube(inter, current_room, (t_room *)connection_lst->content);
			connection_lst = connection_lst->next;
		}
		draw_room(inter, current_room);
		room_lst = room_lst->next;
	}
}

static void	write_start_end(t_interface *inter)
{
	t_room *current_room;

	current_room = inter->data->start;
	mlx_string_put(inter->mlx, inter->win, current_room->x,
		current_room->y - 40, 0x0000FF00, "Start");
	current_room = inter->data->end;
	mlx_string_put(inter->mlx, inter->win, current_room->x,
		current_room->y - 40, 0x00FF0000, "End");
}

void		write_room_info(t_interface *inter)
{
	t_list	*room_lst;
	t_room	*current_room;
	t_point	location;
	int		ant_color;

	room_lst = inter->data->room_list;
	while (room_lst)
	{
		current_room = (t_room *)room_lst->content;
		mlx_string_put(inter->mlx, inter->win, current_room->x,
			current_room->y - 20, 0x00FFFFFF, current_room->label);
		set_point(&location, current_room->x + 1, current_room->y + 1);
		if (current_room->occupant)
		{
			ant_color = get_ant_color(current_room->occupant->number);
			draw_ant(inter, &location, ant_color);
			mlx_string_put(inter->mlx, inter->win, current_room->x,
				current_room->y + ROOM_SIZE, ant_color,
				current_room->occupant->label);
		}
		else
			draw_ant(inter, &location, 0x00000000);
		room_lst = room_lst->next;
	}
	write_start_end(inter);
}
