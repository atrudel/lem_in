/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 16:08:31 by atrudel           #+#    #+#             */
/*   Updated: 2017/04/21 10:19:48 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include "libft.h"
# include "lem_in.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdio.h>
# define INTER ((t_interface *)inter)
# define ABS(x) (x >= 0 ? x : -x)
# define ROOM_SIZE 35

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_image
{
	void		*img_ptr;
	char		*img_addr;
	int			size_x;
	int			size_y;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_image;

typedef struct	s_interface
{
	void		*mlx;
	void		*win;
	t_image		img;
	int			size_x;
	int			size_y;
	t_data		*data;
	void		(*move_func)(t_data *);
}				t_interface;

int				vis_activate();

void			img_erase(t_interface *inter);
void			img_pixel_put(t_interface *inter, int x, int y, int color);
void			draw_line(t_interface *inter, t_point *p1, t_point *p2,
				int color);

t_point			*set_point(t_point *point, int x, int y);
int				get_ant_color(int ant_nb);
void			normalize_coordinates(t_interface *inter);

void			draw_ant(t_interface *inter, t_point *location, int color);
void			write_room_info(t_interface *inter);
void			draw_antheap(t_interface *inter);

void			read_instructions(t_data *data);

#endif
