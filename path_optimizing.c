/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_optimizing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 16:03:59 by atrudel           #+#    #+#             */
/*   Updated: 2017/04/20 13:41:16 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_total_cost(t_list *path_lst)
{
	t_list	*current;
	int		total_cost;

	total_cost = 0;
	current = path_lst;
	while (current)
	{
		if (((t_path *)current->content)->nb_ants > 0)
			if (((t_path *)current->content)->cost > total_cost)
				total_cost = ((t_path *)current->content)->cost;
		current = current->next;
	}
	return (total_cost);
}

int		update_cost(t_path *path, int nb_ant_variation)
{
	path->nb_ants += nb_ant_variation;
	path->cost = path->length + path->nb_ants - 1;
	return (path->cost);
}

void	dispatch_ants(t_data *data, t_list *path_lst)
{
	t_list	*path_to_fill;
	t_list	*path_to_discharge;

	update_cost((t_path *)path_lst->content, data->nb_ants);
	path_to_fill = path_lst;
	while ((path_to_fill = path_to_fill->next))
	{
		while (((t_path *)path_to_fill->content)->cost <
				get_total_cost(path_lst))
		{
			path_to_discharge = path_lst;
			while (path_to_discharge != path_to_fill)
			{
				if (((t_path *)path_to_discharge->content)->cost ==
					get_total_cost(path_lst))
				{
					update_cost((t_path *)path_to_discharge->content, -1);
					update_cost((t_path *)path_to_fill->content, 1);
					break ;
				}
				path_to_discharge = path_to_discharge->next;
			}
		}
	}
}
