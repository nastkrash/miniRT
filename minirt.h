/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:22 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/29 14:13:55 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>	 // printf, perror
# include <stdlib.h>	 // malloc, free, exit
# include <string.h>	 // strerror
# include <unistd.h>	 // open, close, read, write
# include <fcntl.h>	 // open flags (O_RDONLY, O_WRONLY)
# include <errno.h>	 // errno (used with strerror)
# include <stdbool.h> // for bool
# include <math.h>
# include <libft.h>
# include <MLX42.h>

// Allowed functions

// open, close, read, write,
// printf, malloc, free, perror,
// strerror, exit

// all functions from mlx and math

# define WID 800
# define WIN_HEIGHT 800
# ifndef M_PI
#  define M_PI 3.14
# endif
# define CYL_ERROR "Error: Cylinder diameter and height must be a number\n"

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_hit
{
	t_vec3	point;
	t_vec3	normal;
	float	t;
	t_rgb	color;
	bool	hit;
}	t_hit;

typedef struct s_ambient
{
	t_rgb	color;
	bool	is_set;
}	t_ambient;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	orientation;
	int		fov;
	bool	is_set;
}	t_camera;

typedef struct s_light
{
	t_vec3	position;
	float	brightness;
	t_rgb	color;
	bool	is_set;
}	t_light;

typedef struct s_sphere
{
	t_vec3	position;
	float	diameter;
	t_rgb	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	position;
	t_vec3	normal;
	t_rgb	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	position;
	t_vec3	axis;
	float	diameter;
	float	height;
	t_rgb	color;
}	t_cylinder;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
}	t_scene;

typedef struct s_data
{
	void		*mlx;
	mlx_image_t	*img;
	t_scene		scene;
}	t_data;

float	ft_atof(const char *str);
bool	parse_scene(char *file, t_data *data);
bool	process_line(char *line, t_scene *scene);
char	*get_next_line(int fd);
bool	init_mlx(t_data *data);

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_subtract(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_multiply(t_vec3 v, float t);
t_vec3	vec3_divide(t_vec3 v, float t);
float	vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2);
float	vec3_length(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);

void	check_sphere_intersections(t_ray ray, t_list *spheres, t_hit *hit);
void	check_plane_intersections(t_ray ray, t_list *planes, t_hit *hit);
void	check_cylinder_intersections(t_ray ray, t_list *cylinders, t_hit *hit);

t_rgb	calculate_lighting(t_hit *hit, t_scene *scene);
void	render_frame(void *param);
bool	parse_ambient(char **tokens, t_scene *scene);
bool	parse_rgb(char *str, t_rgb *rgb);
bool	ft_is_valid_float(const char *str);
bool	parse_camera(char **tokens, t_scene *scene);
bool	ft_is_valid_int(const char *str);
bool	parse_vec3(char *str, t_vec3 *vec);
bool	validate_vec3_components(t_vec3 *vec);
bool	parse_light(char **tokens, t_scene *scene);
bool	parse_sphere(char **tokens, t_scene *scene);
bool	parse_plane(char **tokens, t_scene *scene);
bool	parse_cylinder(char **tokens, t_scene *scene);
void	ft_free_split(char **split);

#endif
