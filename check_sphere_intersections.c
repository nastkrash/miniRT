/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sphere_intersections.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:27:59 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/21 18:28:00 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline float	calc_t(t_ray ray, t_sphere *sp)
{
	t_vec3	oc;
	float	dis;
	float	a;
	float	b;
	float	t;

	oc = vec3_subtract(ray.origin, sp->position);
	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0f * vec3_dot(oc, ray.direction);
	dis = b * b - 4 * a * (vec3_dot(oc, oc) - sp->diameter * sp->diameter / 4);
	if (dis < 0)
		return (-1.0f);
	t = (-b - sqrt(dis)) / (2.0f * a);
	if (t >= 0)
		return (t);
	t = (-b + sqrt(dis)) / (2.0f * a);
	if (t >= 0)
		return (t);
	return (-1.0f);
}

static inline bool	intersect_sphere(t_ray ray, t_sphere *sphere, t_hit *hit)
{
	float	t;

	t = calc_t(ray, sphere);
	if (t < 0 || t >= hit->t)
		return (false);
	hit->t = t;
	hit->point = vec3_add(ray.origin, vec3_multiply(ray.direction, t));
	hit->normal = vec3_normalize(vec3_subtract(hit->point, sphere->position));
	hit->color = sphere->color;
	hit->hit = true;
	return (true);
}

void	check_sphere_intersections(t_ray ray, t_list *spheres, t_hit *hit)
{
	while (spheres)
	{
		intersect_sphere(ray, (t_sphere *)spheres->content, hit);
		spheres = spheres->next;
	}
}
