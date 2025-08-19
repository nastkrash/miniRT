/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:39 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/21 18:28:40 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	parse_sphere_color(char *color_str, t_sphere *sphere)
{
	if (!parse_rgb(color_str, &sphere->color))
	{
		free(sphere);
		return (printf("Error: Invalid RGB format for sphere\n"), false);
	}
	return (true);
}

static bool	validate_sphere_params(t_sphere *sphere, float diameter)
{
	if (diameter <= 0.0)
	{
		free(sphere);
		return (printf("Error: Sphere diameter must be positive\n"), false);
	}
	return (true);
}

static bool	parse_sphere_position(char *pos_str, t_sphere *sphere)
{
	if (!parse_vec3(pos_str, &sphere->position))
	{
		free(sphere);
		return (printf("Error: Invalid position format for sphere\n"), false);
	}
	return (true);
}

static bool	init_sphere(t_sphere **sphere)
{
	*sphere = malloc(sizeof(t_sphere));
	if (!*sphere)
		return (printf("Error: Memory allocation failed\n"), false);
	return (true);
}

bool	parse_sphere(char **tokens, t_scene *scene)
{
	t_sphere	*sphere;
	float		diameter;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (printf("Error: Invalid sphere format\n"), false);
	if (!ft_is_valid_float(tokens[2]))
		return (printf("Error: Sphere diameter must be a number\n"), false);
	if (!init_sphere(&sphere))
		return (false);
	if (!parse_sphere_position(tokens[1], sphere))
		return (false);
	diameter = ft_atof(tokens[2]);
	if (!validate_sphere_params(sphere, diameter))
		return (false);
	if (!parse_sphere_color(tokens[3], sphere))
		return (false);
	sphere->diameter = diameter;
	ft_lstadd_back(&scene->spheres, ft_lstnew(sphere));
	return (true);
}
