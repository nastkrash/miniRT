/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:35 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/21 18:28:36 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	parse_plane_color(char *color_str, t_plane *plane)
{
	if (!parse_rgb(color_str, &plane->color))
	{
		free(plane);
		return (printf("Error: Invalid RGB format for plane\n"), false);
	}
	return (true);
}

static bool	parse_plane_normal(char *normal_str, t_plane *plane)
{
	if (!parse_vec3(normal_str, &plane->normal))
	{
		free(plane);
		return (printf("Error: Invalid normal format for plane\n"), false);
	}
	if (!validate_vec3_components(&plane->normal))
	{
		free(plane);
		return (printf("Error: Plane normal must be normalized\n"), false);
	}
	return (true);
}

static bool	parse_plane_position(char *pos_str, t_plane *plane)
{
	if (!parse_vec3(pos_str, &plane->position))
	{
		free(plane);
		return (printf("Error: Invalid position format for plane\n"), false);
	}
	return (true);
}

static bool	init_plane(t_plane **plane)
{
	*plane = malloc(sizeof(t_plane));
	if (!*plane)
		return (printf("Error: Memory allocation failed\n"), false);
	return (true);
}

bool	parse_plane(char **tokens, t_scene *scene)
{
	t_plane	*plane;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (printf("Error: Invalid plane format\n"), false);
	if (!init_plane(&plane))
		return (false);
	if (!parse_plane_position(tokens[1], plane))
		return (false);
	if (!parse_plane_normal(tokens[2], plane))
		return (false);
	if (!parse_plane_color(tokens[3], plane))
		return (false);
	ft_lstadd_back(&scene->planes, ft_lstnew(plane));
	return (true);
}
