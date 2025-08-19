/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:18 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/21 18:28:19 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->scene.ambient.is_set = false;
	data->scene.camera.is_set = false;
	data->scene.light.is_set = false;
	data->scene.spheres = NULL;
	data->scene.planes = NULL;
	data->scene.cylinders = NULL;
}

void	cleanup(t_data *data)
{
	if (data->mlx)
		mlx_terminate(data->mlx);
	ft_lstclear(&data->scene.spheres, free);
	ft_lstclear(&data->scene.planes, free);
	ft_lstclear(&data->scene.cylinders, free);
}

bool	check_args(int ac, char **av)
{
	char	*dot;

	if (ac != 2)
		return (printf("Error: Wrong amount of arguments.\n"), false);
	dot = ft_strrchr(av[1], '.');
	if (!dot || (ft_strncmp(dot, ".rt", 4) != 0))
		return (printf("Error: File extension must be .rt\n"), false);
	return (true);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_args(ac, av) == false)
		return (1);
	init_data(&data);
	if (parse_scene(av[1], &data) == false)
		return (cleanup(&data), 1);
	if (init_mlx(&data) == false)
		return (cleanup(&data), 1);
	mlx_loop(data.mlx);
	cleanup(&data);
	return (0);
}
