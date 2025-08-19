/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:46 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/29 14:14:09 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_rgb	ray_color(t_ray ray, t_scene *scene)
{
	t_hit	hit_record;
	t_rgb	color;

	color = (t_rgb){0, 0, 0};
	hit_record.hit = false;
	hit_record.t = INFINITY;
	check_sphere_intersections(ray, scene->spheres, &hit_record);
	check_plane_intersections(ray, scene->planes, &hit_record);
	check_cylinder_intersections(ray, scene->cylinders, &hit_record);
	if (hit_record.hit)
		return (calculate_lighting(&hit_record, scene));
	return (color);
}

static inline float	calc_pixel_x(int x, t_camera *cam)
{
	float	aspect_ratio;
	float	fov_rad;
	float	viewport_height;
	float	viewport_w;

	aspect_ratio = (float)WID / (float)WIN_HEIGHT;
	fov_rad = cam->fov * (M_PI / 180.0f);
	viewport_height = 2.0f * tanf(fov_rad / 2.0f);
	viewport_w = aspect_ratio * viewport_height;
	return ((2.0f * ((x + 0.5f) / WID) - 1.0f) * viewport_w / 2.0f);
}

static inline float	calc_pixel_y(int y, t_camera *cam)
{
	float	fov_rad;
	float	viewport_height;

	fov_rad = cam->fov * (M_PI / 180.0f);
	viewport_height = 2.0f * tanf(fov_rad / 2.0f);
	return ((1.0f - 2.0f * ((y + 0.5f) / WIN_HEIGHT)) * viewport_height / 2.0f);
}

static inline t_ray	calculate_ray(t_camera *cam, int x, int y)
{
	t_ray	ray;
	t_vec3	w;
	t_vec3	u;
	t_vec3	v;

	w = vec3_normalize(vec3_multiply(cam->orientation, -1.0f));
	u = vec3_normalize(vec3_cross((t_vec3){0, 1, 0}, w));
	v = vec3_cross(w, u);
	ray.origin = cam->position;
	ray.direction = vec3_normalize((t_vec3){
			calc_pixel_x(x, cam) * u.x + calc_pixel_y(y, cam) * v.x - w.x,
			calc_pixel_x(x, cam) * u.y + calc_pixel_y(y, cam) * v.y - w.y,
			calc_pixel_x(x, cam) * u.z + calc_pixel_y(y, cam) * v.z - w.z
		});
	return (ray);
}

void	render_frame(void *param)
{
	t_data		*data;
	t_rgb		color;
	int			x;
	int			y;
	uint32_t	*pixels;

	data = (t_data *)param;
	pixels = (uint32_t *)data->img->pixels;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WID)
		{
			color = ray_color(calculate_ray(&data->scene.camera, x, y),
					&data->scene);
			pixels[y * WID + x] = (255 << 24) | (color.b << 16)
				| (color.g << 8) | color.r;
			x++;
		}
		y++;
	}
}
