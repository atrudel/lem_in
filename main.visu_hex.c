/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.visu_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 17:13:57 by atrudel           #+#    #+#             */
/*   Updated: 2017/04/21 09:44:12 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	parse_arguments(int argc, char **argv, t_data *data)
{
	if (argc == 2)
	{
		if (ft_strequ(*argv, "-f"))
		{
			if ((data->fd = open(*(argv + 1), O_RDONLY)) < 0)
			{
				perror(0);
				exit(1);
			}
			return ;
		}
		else
			ft_printf("Unknowned argument: %s\n", *argv);
		ft_printf("Usage: ./visu-hex -f <file_name>\n");
	}
	else if (argc != 0)
		ft_printf("Usage: ./visu-hex -f <file_name>\n");
	exit(-1);
}

int			main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	parse_arguments(argc - 1, argv + 1, &data);
	parse(&data, data.fd);
	if (data.error_fb)
		error_exit("ERROR", &data);
	check_data_validity(&data);
	if (data.error_fb)
		error_exit("ERROR", &data);
	generate_ants(&data);
	vis_activate(&data, read_instructions);
	return (0);
}
