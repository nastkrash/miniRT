/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:30 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/21 18:28:31 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	init_cylinder(t_cylinder **cylinder)
{
	*cylinder = malloc(sizeof(t_cylinder));
	if (!*cylinder)
		return (printf("Error: Memory allocation failed\n"), false);
	return (true);
}

static bool	parse_cyl_pos_axis(char *pos, t_cylinder *cylinder, char *axis)
{
	if (!parse_vec3(pos, &cylinder->position))
	{
		free(cylinder);
		return (printf("Error: Invalid position format for cylinder\n"), false);
	}
	if (!parse_vec3(axis, &cylinder->axis))
	{
		free(cylinder);
		return (printf("Error: Invalid axis format for cylinder\n"), false);
	}
	if (!validate_vec3_components(&cylinder->axis))
	{
		free(cylinder);
		return (printf("Error: Cylinder axis must be normalized\n"), false);
	}
	return (true);
}

static bool	validate_cylinder_dimensions(t_cylinder *cylinder,
	float diameter, float height)
{
	if (diameter <= 0.0 || height <= 0.0)
	{
		free(cylinder);
		return (printf("Error: Cylinder dimensions must be positive\n"), false);
	}
	return (true);
}

static bool	parse_cylinder_color(char *color_str, t_cylinder *cylinder)
{
	if (!parse_rgb(color_str, &cylinder->color))
	{
		free(cylinder);
		return (printf("Error: Invalid RGB format for cylinder\n"), false);
	}
	return (true);
}

bool	parse_cylinder(char **tok, t_scene *scene)
{
	t_cylinder	*cylinder;
	float		diameter;
	float		height;

	if (!tok[1] || !tok[2] || !tok[3] || !tok[4] || !tok[5] || tok[6])
		return (printf("Error: Invalid cylinder format\n"), false);
	if (!ft_is_valid_float(tok[3]) || !ft_is_valid_float(tok[4]))
		return (printf(CYL_ERROR), 0);
	if (!init_cylinder(&cylinder))
		return (false);
	if (!parse_cyl_pos_axis(tok[1], cylinder, tok[2]))
		return (false);
	diameter = ft_atof(tok[3]);
	height = ft_atof(tok[4]);
	if (!validate_cylinder_dimensions(cylinder, diameter, height))
		return (false);
	if (!parse_cylinder_color(tok[5], cylinder))
		return (false);
	cylinder->diameter = diameter;
	cylinder->height = height;
	ft_lstadd_back(&scene->cylinders, ft_lstnew(cylinder));
	return (true);
}
