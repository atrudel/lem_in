/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 16:08:24 by atrudel           #+#    #+#             */
/*   Updated: 2017/04/21 10:08:16 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include "get_next_line.h"

typedef struct s_room	t_room;

typedef struct			s_ant
{
	int					number;
	char				*label;
	t_room				*position;
}						t_ant;

struct					s_room
{
	t_list				*connections;
	t_ant				*occupant;
	char				*label;
	int					x;
	int					y;
	int					start;
	int					end;
	int					visited;
};

typedef struct			s_path
{
	struct s_path		*next;
	t_room				*room;
	int					length;
	int					nb_ants;
	int					cost;
}						t_path;

typedef struct			s_data
{
	int					nb_ants;
	t_list				*room_list;
	t_room				*start;
	t_room				*end;
	t_list				*input;
	t_list				*instructions;
	t_list				*paths;
	t_list				*lst_ants;
	int					x_max;
	int					x_min;
	int					y_max;
	int					y_min;
	int					middle_x;
	int					middle_y;
	int					error;
	int					visualizer;
	int					path_info;
	int					fd;
	char				*error_fb;
}						t_data;

void					parse(t_data *data, int fd);
char					*parse_rooms(t_data *data, int fd);
void					check_data_validity(t_data *data);
void					print_data(t_data *data);
int						rooms_are_valid(t_data *data);
void					skip_comments(t_data *data, int fd, char **line);

int						lst_match_rooms(void *room, void *comparison);
int						lst_match_ants(void *ant, void *comparison);
t_list					*find_paths(t_path *previous, t_room *position,
						t_data *data);
t_path					*get_next_available_path(t_list *path_lst);
void					extend_path(t_path **path, t_room *position,
						t_data *data);
void					set_path_lengths(t_list *paths);
t_path					*get_path_end(t_path *path);
int						compare_paths(void *path1, void *path2);
void					print_paths(t_list *paths);
void					delete_path(t_path **path);
t_path					*copy_path(t_path *path, t_data *data);
int						paths_overlap(t_path *path1, t_path *path2);
void					set_as_visited(t_path *path);
void					set_as_unvisited(t_path *path);

void					bfs(t_data *data);

void					optimize_paths(t_data *data);
void					dispatch_ants(t_data *data, t_list *path_lst);
void					do_one_turn(t_data *data);

t_ant					*create_new_ant(t_data *data);
void					generate_ants(t_data *data);
int						move_ant(t_ant *ant, t_room *destination);
t_ant					*start_next_ant(t_data *data);
int						finished(t_data *data);

void					data_reinit(t_data *data);
void					lst_delete_room(void *content, size_t size);
void					lst_delete_path(void *content, size_t size);
void					delete_data(t_data *data);
t_list					*extend_lst(t_list **lst, void *content, t_data *data);
t_list					*extend_lst_beginning(t_list **lst, void *content,
						t_data *data);
void					lst_free_content(void *content, size_t size);

void					error_exit(char *message, t_data *data);

#endif
