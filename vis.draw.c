/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 16:08:34 by atrudel           #+#    #+#             */
/*   Updated: 2017/04/20 13:51:44 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "lem_in.h"

void	draw_ant(t_interface *inter, t_point *location, int color)
{
	t_image			ant_img;
	int				*pixel_addr;

	ant_img.img_ptr = mlx_xpm_file_to_image(inter->mlx, "rsz_ant.xpm",
						&ant_img.size_x, &ant_img.size_y);
	ant_img.img_addr = mlx_get_data_addr(ant_img.img_ptr,
		&ant_img.bits_per_pixel, &ant_img.size_line, &ant_img.endian);
	if (ant_img.bits_per_pixel != 32)
		error_exit("Wrong bits_per_pixel paremeters. Fix in draw_ant funct",
		inter->data);
	pixel_addr = (int *)ant_img.img_addr;
	while (pixel_addr < (int *)ant_img.img_addr +
			ant_img.size_x * ant_img.size_y)
	{
		*pixel_addr = *pixel_addr & color;
		pixel_addr++;
	}
	mlx_put_image_to_window(inter->mlx, inter->win, ant_img.img_ptr,
						location->x, location->y);
	mlx_destroy_image(inter->mlx, ant_img.img_ptr);
}
