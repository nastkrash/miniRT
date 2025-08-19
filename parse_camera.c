/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:28 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/21 18:28:29 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	validate_camera_params(t_scene *scene, t_vec3 *orientation, int fov)
{
	if (scene->camera.is_set)
		return (printf("Error: Camera already defined\n"), false);
	if (!validate_vec3_components(orientation))
		return (printf("Error: Camera orientation must be normalized\n"), 0);
	if (fov < 0 || fov > 180)
		return (printf("Error: FOV must be between 0 and 180\n"), false);
	return (true);
}

bool	parse_camera(char **tokens, t_scene *scene)
{
	t_vec3	position;
	t_vec3	orientation;
	int		fov;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (printf("Error: Invalid camera format\n"), false);
	if (!parse_vec3(tokens[1], &position))
		return (printf("Error: Invalid position format for camera\n"), false);
	if (!parse_vec3(tokens[2], &orientation))
		return (printf("Error: Invalid orientation format for camera\n"), 0);
	if (!ft_is_valid_int(tokens[3]))
		return (printf("Error: FOV ratio be an integer\n"), false);
	fov = ft_atoi(tokens[3]);
	if (!validate_camera_params(scene, &orientation, fov))
		return (false);
	scene->camera.position = position;
	scene->camera.orientation = orientation;
	scene->camera.fov = fov;
	scene->camera.is_set = true;
	return (true);
}
