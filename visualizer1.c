/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 16:08:10 by atrudel           #+#    #+#             */
/*   Updated: 2017/04/21 10:23:05 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

int		keyboard(int keycode, t_interface *inter)
{
	if (keycode == 53 || keycode == 12)
	{
		if (inter->data->fd)
			if (close(inter->data->fd) < 0)
				perror(0);
		delete_data(inter->data);
		mlx_destroy_image(inter->mlx, inter->img.img_ptr);
		mlx_destroy_window(inter->mlx, inter->win);
		exit(0);
	}
	if (keycode == 49)
		inter->move_func(inter->data);
	return (0);
}

int		vis_display(void *inter)
{
	img_erase((t_interface *)inter);
	draw_antheap((t_interface *)inter);
	mlx_put_image_to_window(((t_interface *)inter)->mlx,
							((t_interface *)inter)->win,
							((t_interface *)inter)->img.img_ptr, 0, 0);
	write_room_info(inter);
	return (0);
}

int		vis_activate(t_data *data, void (*move_func)(t_data *))
{
	t_interface	inter;

	ft_bzero(&inter, sizeof(inter));
	inter.data = data;
	inter.size_y = 1100;
	inter.size_x = 2000;
	inter.move_func = move_func;
	normalize_coordinates(&inter);
	inter.mlx = mlx_init();
	inter.win = mlx_new_window(inter.mlx, inter.size_x, inter.size_y,
		"Lem-in Visualizer");
	inter.img.img_ptr = mlx_new_image(inter.mlx, inter.size_x, inter.size_y);
	inter.img.size_x = inter.size_x;
	inter.img.size_y = inter.size_y;
	inter.img.img_addr = mlx_get_data_addr(inter.img.img_ptr,
			&inter.img.bits_per_pixel, &inter.img.size_line, &inter.img.endian);
	mlx_hook(inter.win, 2, 1L << 0, keyboard, &inter);
	mlx_loop_hook(inter.mlx, vis_display, &inter);
	mlx_loop(inter.mlx);
	return (0);
}
