/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 15:43:38 by atrudel           #+#    #+#             */
/*   Updated: 2017/04/28 14:27:29 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		add_room(t_data *data, t_room *new_room)
{
	t_room	*twin;
	t_list	*new_lst;

	if ((twin = (t_room *)ft_lstfind(data->room_list, lst_match_rooms,
		new_room->label)))
	{
		if (twin->x != new_room->x || twin->y != new_room->y)
		{
			ft_asprintf(&data->error_fb, "Room named '%s'\
			\nis listed twice with different coordinates.\
			\nSecond mention at line %i\n",
			new_room->label, ft_lstsize(data->input) + 1);
			error_exit("ERROR", data);
		}
		ft_strdel(&new_room->label);
	}
	else
	{
		if (!(new_lst = ft_lstnew(new_room, sizeof(*new_room))))
			error_exit("ERROR: malloc failed during room list creation", data);
		ft_lstadd_end(&data->room_list, new_lst);
	}
}

static int	parse_room_line(t_room *new, char *line, t_data *data)
{
	char *ptr;

	ptr = line;
	if (get_next_string(&ptr, &new->label) > 0 && get_next_int(&ptr,
		&new->x) && get_next_int(&ptr, &new->y) && *ptr == 0)
	{
		if (*(new->label) == 'L' || ft_strchr(new->label, '-'))
		{
			ft_asprintf(&data->error_fb, "Bad room name: %s\n", new->label);
			error_exit("ERROR", data);
		}
		return (1);
	}
	ft_strdel(&new->label);
	return (0);
}

static char	*finish_room_parsing(t_room *new, char *line)
{
	if (!new->start && !new->end)
		return (line);
	ft_strdel(&line);
	return (NULL);
}

char		*parse_rooms(t_data *data, int fd)
{
	char	*line;
	t_room	new;

	ft_bzero(&new, sizeof(new));
	while (get_next_line(fd, &line) > 0)
	{
		skip_comments(data, fd, &line);
		if (ft_strequ(line, "##start"))
			new.start = 1;
		else if (ft_strequ(line, "##end"))
			new.end = 1;
		else
		{
			if (parse_room_line(&new, line, data))
				add_room(data, &new);
			else
				return (finish_room_parsing(&new, line));
			ft_bzero(&new, sizeof(new));
		}
		extend_lst(&data->input, line, data);
	}
	ft_strdel(&line);
	return (NULL);
}

void		skip_comments(t_data *data, int fd, char **line)
{
	int	ret;

	ret = 1;
	while (ret && line && *line && **line == '#' &&
		!ft_strequ_mult(*line, 2, "##start", "##end"))
	{
		extend_lst(&data->input, *line, data);
		ret = get_next_line(fd, line);
	}
}
