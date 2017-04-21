/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:19:26 by atrudel           #+#    #+#             */
/*   Updated: 2017/04/20 12:19:29 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	is_tube(t_data *data, char *line, t_room **first, t_room **second)
{
	char	*name;
	int		ret;

	name = NULL;
	ret = 0;
	while (*line && *line != '-')
		name = ft_strappend_char(name, *line++);
	if (*line++ == '-' &&
	(*first = ft_lstfind(data->room_list, lst_match_rooms, name)) &&
	(*second = ft_lstfind(data->room_list, lst_match_rooms, line)))
		ret = 1;
	ft_strdel(&name);
	return (ret);
}

static void	parse_tubes(t_data *data, char *line, int fd)
{
	int		ret;
	t_room	*first;
	t_room	*second;

	ret = 1;
	while (ret > 0)
	{
		if (is_tube(data, line, &first, &second))
		{
			extend_lst(&first->connections, second, data);
			extend_lst(&second->connections, first, data);
		}
		else if (!(*line == '#' &&
		!ft_strequ_mult(line, 2, "##start", "##end")))
			break ;
		extend_lst(&data->input, line, data);
		ret = get_next_line(fd, &line);
	}
	ft_strdel(&line);
}

static void	set_start_end(t_data *data)
{
	int		start;
	int		end;
	t_list	*current;

	start = 0;
	end = 0;
	current = data->room_list;
	while (current)
	{
		if (((t_room *)current->content)->start)
		{
			start++;
			data->start = (t_room *)current->content;
		}
		if (((t_room *)current->content)->end)
		{
			end++;
			data->end = (t_room *)current->content;
		}
		current = current->next;
	}
	if (start == 1 && end == 1)
		return ;
	ft_asprintf(&data->error_fb, "%i start rooms and %i end rooms", start, end);
	error_exit("ERROR", data);
}

void		check_data_validity(t_data *data)
{
	if (data->nb_ants <= 0)
		ft_asprintf(&data->error_fb, "Need more than 0 ants\n");
	else if (!ft_lstsize(data->room_list))
		ft_asprintf(&data->error_fb, "No room\n");
	else if (data->start == data->end && data->start != 0)
		ft_asprintf(&data->error_fb, "Start room is the same as End room\n");
}

void		parse(t_data *data, int fd)
{
	char	*line;

	if (get_next_line(fd, &line) > 0)
	{
		skip_comments(data, fd, &line);
		if (ft_atoi_error(line, &data->nb_ants))
		{
			extend_lst(&data->input, line, data);
			if ((line = parse_rooms(data, fd)))
			{
				set_start_end(data);
				parse_tubes(data, line, fd);
			}
			else if (!data->error_fb)
				ft_asprintf(&data->error_fb, "No tube info");
		}
		else
			ft_asprintf(&data->error_fb, "Nb ants: incorrect format\n");
	}
	else
		ft_asprintf(&data->error_fb, "No input\n");
}
