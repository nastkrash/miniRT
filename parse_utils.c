/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:41 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/21 18:28:42 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	ft_is_valid_int(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	ft_is_valid_float(const char *str)
{
	bool	has_digits;

	if (str == NULL || *str == '\0')
		return (false);
	if (*str == '+' || *str == '-')
		if (*(++str) == '\0')
			return (false);
	has_digits = false;
	while (ft_isdigit(*str))
	{
		has_digits = true;
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			has_digits = true;
			str++;
		}
	}
	return (*str == '\0' && has_digits);
}

bool	parse_rgb(char *str, t_rgb *rgb)
{
	char	**split;
	int		count;

	split = ft_split(str, ',');
	if (!split)
		return (false);
	count = 0;
	while (split[count])
		count++;
	if (count != 3)
		return (ft_free_split(split), false);
	if (!ft_is_valid_int(split[0])
		|| !ft_is_valid_int(split[1]) || !ft_is_valid_int(split[2]))
		return (ft_free_split(split),
			printf("Error: RGB values must be integers\n"), false);
	rgb->r = ft_atoi(split[0]);
	rgb->g = ft_atoi(split[1]);
	rgb->b = ft_atoi(split[2]);
	ft_free_split(split);
	if (rgb->r < 0 || rgb->r > 255
		|| rgb->g < 0 || rgb->g > 255
		|| rgb->b < 0 || rgb->b > 255)
		return (false);
	return (true);
}

bool	parse_vec3(char *str, t_vec3 *vec)
{
	char	**split;
	int		count;

	split = ft_split(str, ',');
	if (!split)
		return (false);
	count = 0;
	while (split[count])
		count++;
	if (count != 3)
	{
		ft_free_split(split);
		return (false);
	}
	if (!ft_is_valid_float(split[0])
		|| !ft_is_valid_float(split[1]) || !ft_is_valid_float(split[2]))
	{
		ft_free_split(split);
		return (printf("Error: Vector values must be numeric\n"), false);
	}
	vec->x = ft_atof(split[0]);
	vec->y = ft_atof(split[1]);
	vec->z = ft_atof(split[2]);
	ft_free_split(split);
	return (true);
}

bool	validate_vec3_components(t_vec3 *vec)
{
	if (vec->x < -1.0 || vec->x > 1.0
		|| vec->y < -1.0 || vec->y > 1.0
		|| vec->z < -1.0 || vec->z > 1.0)
		return (false);
	return (true);
}
