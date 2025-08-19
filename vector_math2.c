/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:50 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/21 18:28:51 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}

float	vec3_length(t_vec3 v)
{
	return (sqrt(vec3_dot(v, v)));
}

t_vec3	vec3_normalize(t_vec3 v)
{
	float	length;

	length = vec3_length(v);
	if (length < 0.0001f)
		return ((t_vec3){0.0f, 0.0f, 0.0f});
	return (vec3_divide(v, length));
}
