/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:33 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/21 18:28:34 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	validate_light_params(t_scene *scene, float brightness)
{
	if (scene->light.is_set)
		return (printf("Error: Light already defined\n"), false);
	if (brightness < 0.0 || brightness > 1.0)
		return (printf("Error: Light brightness must be between 0.0 and 1.0\n"),
			false);
	return (true);
}

bool	parse_light(char **tokens, t_scene *scene)
{
	t_vec3	position;
	float	brightness;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (printf("Error: Invalid light format\n"), false);
	if (!parse_vec3(tokens[1], &position))
		return (printf("Error: Invalid position format for light\n"), false);
	if (!ft_is_valid_float(tokens[2]))
		return (printf("Error: Light brightness must be a number\n"), false);
	brightness = ft_atof(tokens[2]);
	if (!validate_light_params(scene, brightness))
		return (false);
	if (!parse_rgb(tokens[3], &scene->light.color))
		return (printf("Error: Invalid RGB format for light\n"), false);
	scene->light.position = position;
	scene->light.brightness = brightness;
	scene->light.is_set = true;
	return (true);
}
