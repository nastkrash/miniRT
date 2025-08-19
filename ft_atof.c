/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:02 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/21 18:28:03 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline static int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

inline static int	process_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	return (sign);
}

inline static double	process_integer_part(const char **str)
{
	double	result;

	result = 0.0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	return (result);
}

inline static double	process_fraction(const char **str)
{
	double	fraction;
	double	result;

	result = 0.0;
	fraction = 0.1;
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			result += (**str - '0') * fraction;
			fraction *= 0.1;
			(*str)++;
		}
	}
	return (result);
}

float	ft_atof(const char *str)
{
	int		sign;
	double	result;

	if (!str)
		return (0.0);
	while (ft_is_space(*str))
		str++;
	sign = process_sign(&str);
	result = process_integer_part(&str);
	result += process_fraction(&str);
	return (result * sign);
}
