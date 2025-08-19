/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:48 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/21 18:28:49 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vec3	vec3_subtract(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vec3	vec3_multiply(t_vec3 v, float t)
{
	t_vec3	result;

	result.x = v.x * t;
	result.y = v.y * t;
	result.z = v.z * t;
	return (result);
}

t_vec3	vec3_divide(t_vec3 v, float t)
{
	t_vec3	result;

	if (t == 0.0f)
		t = 0.0001f;
	result.x = v.x / t;
	result.y = v.y / t;
	result.z = v.z / t;
	return (result);
}

float	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
