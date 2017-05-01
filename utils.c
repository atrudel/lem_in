/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 17:17:45 by atrudel           #+#    #+#             */
/*   Updated: 2017/04/28 14:13:25 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_exit(char *message, t_data *data)
{
	ft_putendl(message);
	if (data->error)
		ft_putstr_fd(data->error_fb, 2);
	delete_data(data);
	exit(-1);
}

void	data_reinit(t_data *data)
{
	t_list	*current;

	current = data->room_list;
	while (current)
	{
		((t_room *)current->content)->visited = 0;
		current = current->next;
	}
}
