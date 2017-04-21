/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.lem_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 16:08:04 by atrudel           #+#    #+#             */
/*   Updated: 2017/04/20 12:13:38 by atrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "visualizer.h"

static void	usage(char *arg)
{
	ft_printf("Unknowned argument: %s\n", arg);
	ft_printf("lem-in usage: ./lem-in <options>\n");
	ft_printf("\t-vis :\t enable visualizer\n");
	ft_printf("\t-error:\t display error details\n");
	ft_printf("\t-path:\t display chosen path(s)\n");
}

static void	parse_arguments(int argc, char **argv, t_data *data)
{
	while (argc > 0)
	{
		if (ft_strequ(*argv, "-vis"))
			data->visualizer = 1;
		else if (ft_strequ(*argv, "-error"))
			data->error = 1;
		else if (ft_strequ(*argv, "-path"))
			data->path_info = 1;
		else
		{
			usage(*argv);
			exit(1);
		}
		argv++;
		argc--;
	}
}

int			main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	parse_arguments(argc - 1, argv + 1, &data);
	parse(&data, 0);
	if (data.error_fb)
		error_exit("ERROR", &data);
	check_data_validity(&data);
	if (data.error_fb)
		error_exit("ERROR", &data);
	bfs(&data);
	generate_ants(&data);
	dispatch_ants(&data, data.paths);
	ft_lstprint(data.input);
	ft_printf("\n");
	if (data.path_info)
		print_paths(data.paths);
	if (data.visualizer)
		vis_activate(&data, do_one_turn);
	else
		while (!finished(&data))
			do_one_turn(&data);
	delete_data(&data);
	sleep(1);
	return (0);
}
