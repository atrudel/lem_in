/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 11:37:37 by atrudel           #+#    #+#             */
/*   Updated: 2017/03/21 17:59:01 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		lst_match_rooms(void *room, void *comparison)
{
	if (room && ft_strequ(((t_room *)room)->label, (char *)comparison))
		return (1);
	return (0);
}

int		lst_match_ants(void *ant, void *comparison)
{
	if (ant && ft_strequ(((t_ant *)ant)->label, (char *)comparison))
		return (1);
	return (0);
}

t_list	*extend_lst(t_list **lst, void *content, t_data *data)
{
	t_list *new;

	if (!(new = ft_lstnew_nocopy(content, 0)))
		error_exit("Malloc failed during list construction", data);
	ft_lstadd_end(lst, new);
	return (*lst);
}

t_list	*extend_lst_beginning(t_list **lst, void *content, t_data *data)
{
	t_list *new;

	if (!(new = ft_lstnew_nocopy(content, 0)))
		error_exit("Malloc failed during list construction", data);
	ft_lstadd(lst, new);
	return (*lst);
}

void	lst_free_content(void *content, size_t size)
{
	(void)size;
	free(content);
}
