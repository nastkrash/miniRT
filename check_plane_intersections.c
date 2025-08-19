/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane_intersections.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:27:57 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/23 14:56:10 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline bool	intersect_plane(t_ray ray, t_plane *plane, t_hit *hit)
{
	float	denom;
	t_vec3	plane_to_ray;
	float	t;

	denom = vec3_dot(ray.direction, plane->normal);
	if (fabs(denom) < 0.0001f)
		return (false);
	plane_to_ray = vec3_subtract(plane->position, ray.origin);
	t = vec3_dot(plane_to_ray, plane->normal) / denom;
	if (t < 0)
		return (false);
	if (t < hit->t)
	{
		hit->t = t;
		hit->point = vec3_add(ray.origin, vec3_multiply(ray.direction, t));
		if (denom > 0)
			hit->normal = vec3_multiply(plane->normal, -1.0f);
		else
			hit->normal = plane->normal;
		hit->color = plane->color;
		hit->hit = true;
		return (true);
	}
	return (false);
}

void	check_plane_intersections(t_ray ray, t_list *planes, t_hit *hit)
{
	while (planes)
	{
		intersect_plane(ray, (t_plane *)planes->content, hit);
		planes = planes->next;
	}
}
