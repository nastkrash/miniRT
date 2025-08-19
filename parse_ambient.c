/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:25 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/21 18:28:26 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	validate_ambient_params(t_scene *scene, float ratio)
{
	if (scene->ambient.is_set)
		return (printf("Error: Ambient lighting already defined\n"), false);
	if (ratio < 0.0 || ratio > 1.0)
		return (printf("Error: Ambient ratio must be between 0.0 and 1.0\n"),
			false);
	return (true);
}

bool	parse_ambient(char **tokens, t_scene *scene)
{
	float	ratio;

	if (!tokens[1] || !tokens[2] || tokens[3])
		return (printf("Error: Invalid ambient lighting format\n"), false);
	if (!ft_is_valid_float(tokens[1]))
		return (printf("Error: Ambient ratio must be a number\n"), false);
	ratio = ft_atof(tokens[1]);
	if (!validate_ambient_params(scene, ratio))
		return (false);
	if (!parse_rgb(tokens[2], &scene->ambient.color))
		return (printf("Error: Invalid RGB format for ambient lighting\n"), 0);
	scene->ambient.color.r = (int)(scene->ambient.color.r * ratio);
	scene->ambient.color.g = (int)(scene->ambient.color.g * ratio);
	scene->ambient.color.b = (int)(scene->ambient.color.b * ratio);
	scene->ambient.is_set = true;
	return (true);
}
