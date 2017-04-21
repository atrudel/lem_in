/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 16:08:27 by atrudel           #+#    #+#             */
/*   Updated: 2017/04/20 13:52:08 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	img_erase(t_interface *inter)
{
	ft_bzero(inter->img.img_addr, inter->img.bits_per_pixel / 8
			* inter->img.size_x * inter->img.size_y);
}

void	img_pixel_put(t_interface *inter, int x, int y, int color)
{
	char			*pixel_addr;
	int				bytes_per_pixel;
	unsigned int	color_code;
	int				i;
	int				j;

	if (x >= 0 && x < inter->size_x && y >= 0 && y < inter->size_y)
	{
		bytes_per_pixel = inter->img.bits_per_pixel / 8;
		pixel_addr = inter->img.img_addr;
		pixel_addr += y * inter->img.size_line;
		pixel_addr += x * bytes_per_pixel;
		color_code = mlx_get_color_value(inter->mlx, color);
		i = 0;
		j = inter->img.endian ? bytes_per_pixel : 0;
		while (i < bytes_per_pixel)
		{
			ft_memcpy(pixel_addr + i, (char *)&color_code + j, 1);
			i++;
			inter->img.endian ? j-- : j++;
		}
	}
}

void	draw_line_horiz(t_interface *inter, t_point *p1, t_point *p2, int color)
{
	int x;
	int y;
	int dx;
	int dy;
	int error;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	x = p1->x;
	y = p1->y;
	error = 0;
	while (x <= p2->x)
	{
		img_pixel_put(inter, x, y, color);
		error += ABS(dy);
		if (error >= dx)
		{
			dy >= 0 ? y++ : y--;
			error -= dx;
		}
		x++;
	}
}

void	draw_line_vertic(t_interface *inter, t_point *p1, t_point *p2,
						int color)
{
	int x;
	int y;
	int dx;
	int dy;
	int error;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	x = p1->x;
	y = p1->y;
	error = 0;
	while (y <= p2->y)
	{
		img_pixel_put(inter, x, y, color);
		error += ABS(dx);
		if (error >= dy)
		{
			dx >= 0 ? x++ : x--;
			error -= dy;
		}
		y++;
	}
}

void	draw_line(t_interface *inter, t_point *p1, t_point *p2, int color)
{
	int dx;
	int dy;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	if (ABS(dx) >= ABS(dy))
	{
		if (dx >= 0)
			draw_line_horiz(inter, p1, p2, color);
		else
			draw_line_horiz(inter, p2, p1, color);
	}
	else
	{
		if (dy >= 0)
			draw_line_vertic(inter, p1, p2, color);
		else
			draw_line_vertic(inter, p2, p1, color);
	}
}
