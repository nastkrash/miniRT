/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_lighting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:27:45 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/21 18:27:47 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline bool	ray_hits_anything(t_ray ray, t_scene *scene, float max_dist)
{
	t_hit	hit;

	hit.hit = false;
	hit.t = max_dist;
	check_sphere_intersections(ray, scene->spheres, &hit);
	if (hit.hit)
		return (true);
	check_plane_intersections(ray, scene->planes, &hit);
	if (hit.hit)
		return (true);
	check_cylinder_intersections(ray, scene->cylinders, &hit);
	return (hit.hit);
}

static inline bool	is_in_shadow(t_vec3 point, t_vec3 light_pos, t_scene *scene)
{
	t_ray	shadow_ray;
	float	light_distance;
	t_vec3	light_dir;
	t_vec3	shadow_bias;

	light_dir = vec3_subtract(light_pos, point);
	light_distance = vec3_length(light_dir);
	shadow_bias = vec3_multiply(vec3_normalize(light_dir), 0.001f);
	shadow_ray.origin = vec3_add(point, shadow_bias);
	shadow_ray.direction = vec3_normalize(light_dir);
	return (ray_hits_anything(shadow_ray, scene, light_distance));
}

static inline t_rgb	calculate_diffuse(t_hit *hit, t_light *light,
										t_vec3 light_dir)
{
	t_rgb	color;
	float	intensity;

	intensity = fmaxf(0.0f, vec3_dot(hit->normal, light_dir));
	intensity *= light->brightness;
	color.r = (int)(light->color.r * intensity);
	color.g = (int)(light->color.g * intensity);
	color.b = (int)(light->color.b * intensity);
	return (color);
}

t_rgb	calculate_lighting(t_hit *hit, t_scene *s)
{
	t_rgb	res;
	t_rgb	diff_clr;
	t_vec3	light_dir;

	diff_clr = (t_rgb){0, 0, 0};
	light_dir = vec3_subtract(s->light.position, hit->point);
	light_dir = vec3_normalize(light_dir);
	if (!is_in_shadow(hit->point, s->light.position, s))
		diff_clr = calculate_diffuse(hit, &s->light, light_dir);
	res.r = fminf(255, (s->ambient.color.r + diff_clr.r) * hit->color.r / 255);
	res.g = fminf(255, (s->ambient.color.g + diff_clr.g) * hit->color.g / 255);
	res.b = fminf(255, (s->ambient.color.b + diff_clr.b) * hit->color.b / 255);
	return (res);
}
