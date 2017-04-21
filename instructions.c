/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 17:04:37 by atrudel           #+#    #+#             */
/*   Updated: 2017/03/20 11:23:46 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

int		apply_instruction(char *instruction, t_data *data)
{
	char	*ant_label;
	t_ant	*ant;
	t_room	*destination;

	ant_label = NULL;
	while (*instruction && *instruction != '-')
		ant_label = ft_strappend_char(ant_label, *instruction++);
	if ((ant = ft_lstfind(data->lst_ants, lst_match_ants, ant_label)))
	{
		ft_strdel(&ant_label);
		if (*instruction++ == '-')
		{
			if ((destination = ft_lstfind(data->room_list, lst_match_rooms,
				instruction)))
				return (move_ant(ant, destination));
		}
		else
			ft_printf("Bad instruction formatting\n");
	}
	else
	{
		ft_printf("Unknowned ant: %s\n", ant_label);
		ft_strdel(&ant_label);
	}
	return (0);
}

void	read_instructions(t_data *data)
{
	char	*line;
	char	**instructions;
	int		i;

	if (get_next_line(0, &line) > 0)
	{
		instructions = ft_strsplit(line, ' ');
		i = 0;
		while (instructions[i])
		{
			apply_instruction(instructions[i], data);
			ft_strdel(&instructions[i]);
			i++;
		}
		free(instructions);
	}
	ft_strdel(&line);
}
