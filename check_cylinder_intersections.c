/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder_intersections.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:27:50 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/21 18:27:51 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline float	calc_t_border(t_cylinder *cy, t_ray ray, t_vec3 oc)
{
	float	t;
	float	a;
	float	b;
	float	dis;
	float	ddo;

	ddo = vec3_dot(oc, vec3_normalize(cy->axis));
	dis = vec3_dot(ray.direction, vec3_normalize(cy->axis));
	a = vec3_dot(ray.direction, ray.direction) - dis * dis;
	b = 2 * (vec3_dot(ray.direction, oc) - dis * ddo);
	t = vec3_dot(oc, oc) - ddo * ddo - cy->diameter * cy->diameter / 4.0f;
	dis = b * b - 4 * a * t;
	if (dis < 0)
		return (-1.0f);
	t = (-b - sqrt(dis)) / (2 * a);
	if (t < 0)
		t = (-b + sqrt(dis)) / (2 * a);
	return (t);
}

static inline bool	update_hit(t_ray ray, float t, t_cylinder *c, t_hit *hit)
{
	t_vec3	hp;
	t_vec3	axis_component;
	float	h_proj;

	hp = vec3_add(ray.origin, vec3_multiply(ray.direction, t));
	h_proj = vec3_dot(vec3_subtract(hp, c->position), vec3_normalize(c->axis));
	if (h_proj < 0 || h_proj > c->height)
		return (false);
	hit->t = t;
	hit->point = hp;
	hp = vec3_subtract(hp, c->position);
	axis_component = vec3_multiply(vec3_normalize(c->axis), h_proj);
	hit->normal = vec3_normalize(vec3_subtract(hp, axis_component));
	hit->color = c->color;
	hit->hit = true;
	return (true);
}

inline static void	cy_cap(t_ray ray, t_cylinder cy, t_hit *hit, t_vec3 pos)
{
	float	denom;
	float	t;
	t_vec3	f_c;
	float	dist_sq;
	t_vec3	hit_point;

	cy.axis = vec3_normalize(cy.axis);
	denom = vec3_dot(ray.direction, cy.axis);
	if (fabs(denom) <= 0.0001f)
		return ;
	t = vec3_dot(vec3_subtract(pos, ray.origin), cy.axis) / denom;
	if (t <= 0 || t >= hit->t)
		return ;
	hit_point = vec3_add(ray.origin, vec3_multiply(ray.direction, t));
	f_c = vec3_subtract(hit_point, pos);
	dist_sq = vec3_dot(f_c, f_c) - pow(vec3_dot(f_c, cy.axis), 2);
	if (dist_sq > cy.diameter * cy.diameter / 4.0f)
		return ;
	hit->t = t;
	hit->point = hit_point;
	hit->normal = vec3_multiply(cy.axis, -1.0f);
	if (denom < 0)
		hit->normal = cy.axis;
	hit->color = cy.color;
	hit->hit = true;
}

void	intersect_cylinder(t_ray ray, t_cylinder *cy, t_hit *hit)
{
	float	t;
	t_vec3	top_pos;

	t = calc_t_border(cy, ray, vec3_subtract(ray.origin, cy->position));
	if (t > 0 && t < hit->t)
		if (update_hit(ray, t, cy, hit))
			hit->t = t;
	cy_cap(ray, *cy, hit, cy->position);
	top_pos = vec3_multiply(vec3_normalize(cy->axis), cy->height);
	top_pos = vec3_add(cy->position, top_pos);
	cy_cap(ray, *cy, hit, top_pos);
}

void	check_cylinder_intersections(t_ray ray, t_list *cylinders, t_hit *hit)
{
	while (cylinders)
	{
		intersect_cylinder(ray, (t_cylinder *)cylinders->content, hit);
		cylinders = cylinders->next;
	}
}
