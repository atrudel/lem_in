/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:16:38 by atrudel           #+#    #+#             */
/*   Updated: 2017/04/17 14:13:27 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ant	*create_new_ant(t_data *data)
{
	static int	number = 1;
	t_ant		*new_ant;

	if (!(new_ant = (t_ant *)malloc(sizeof(t_ant))))
		error_exit("Malloc failed during ant creation", data);
	new_ant->number = number;
	new_ant->label = ft_itoa(number);
	new_ant->label = ft_strappend_char_before(new_ant->label, 'L');
	new_ant->position = data->start;
	number++;
	return (new_ant);
}

void	generate_ants(t_data *data)
{
	int		count;

	count = 1;
	while (count <= data->nb_ants)
	{
		extend_lst(&data->lst_ants, create_new_ant(data), data);
		count++;
	}
}

t_ant	*start_next_ant(t_data *data)
{
	t_list	*ant_lst;

	ant_lst = data->lst_ants;
	while (ant_lst)
	{
		if (((t_ant *)ant_lst->content)->position->start)
			return ((t_ant *)ant_lst->content);
		ant_lst = ant_lst->next;
	}
	return (NULL);
}

int		move_ant(t_ant *ant, t_room *destination)
{
	if (ft_lstfind(ant->position->connections, lst_match_rooms,
		destination->label))
	{
		if (!destination->occupant || destination->end)
		{
			ant->position->occupant = NULL;
			ant->position = destination;
			destination->occupant = ant;
			return (1);
		}
		else
			ft_printf("Room '%s' is already occupied by %s\n",
			destination->label, destination->occupant->label);
	}
	else
		ft_printf("%s can't move to room '%s'\n", ant->label,
		destination->label);
	return (0);
}

int		finished(t_data *data)
{
	t_list	*ant;

	ant = data->lst_ants;
	while (ant)
	{
		if (!((t_ant *)ant->content)->position->end)
			return (0);
		ant = ant->next;
	}
	return (1);
}
