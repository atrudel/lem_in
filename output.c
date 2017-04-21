/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 15:46:25 by atrudel           #+#    #+#             */
/*   Updated: 2017/03/23 16:24:29 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_paths(t_list *paths)
{
	t_path	*node;
	int		i;

	i = 1;
	while (paths)
	{
		node = (t_path *)paths->content;
		if (node && node->nb_ants)
		{
			ft_printf("Path %i (length=%i, with %i ants: cost=%i):\n",
			i, node->length, node->nb_ants, node->cost);
			ft_printf("\t%s", node->room->label);
			while ((node = node->next))
				ft_printf("->%s", node->room->label);
		}
		ft_printf("\n");
		paths = paths->next;
		i++;
	}
	ft_printf("\n");
}

void	print_instruction_line(t_data *data)
{
	int	start;

	start = 1;
	while (data->instructions)
	{
		if (!start)
			ft_printf(" ");
		start = 0;
		ft_printf("%s", data->instructions->content);
		ft_lstremove(&data->instructions, data->instructions, lst_free_content);
	}
	ft_printf("\n");
}

void	all_ants_one_step(t_data *data, t_path *path)
{
	t_path	*destination;
	t_path	*origin;
	t_ant	*ant_to_move;
	char	*instruction;

	origin = path;
	destination = get_path_end(path);
	while (!destination->room->start)
	{
		while (origin->next != destination)
			origin = origin->next;
		if (origin->room->start)
			ant_to_move = start_next_ant(data);
		else
			ant_to_move = origin->room->occupant;
		if (ant_to_move)
		{
			move_ant(ant_to_move, origin->next->room);
			ft_asprintf(&instruction, "%s-%s", ant_to_move->label,
			origin->next->room->label);
			extend_lst(&data->instructions, instruction, data);
		}
		destination = origin;
		origin = path;
	}
}

void	do_one_turn(t_data *data)
{
	t_list	*current;

	current = data->paths;
	while (!finished(data) && current)
	{
		all_ants_one_step(data, (t_path *)current->content);
		current = current->next;
	}
	print_instruction_line(data);
}
