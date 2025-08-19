/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:43 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/29 12:08:48 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

static char	**tokenize_line(char *line)
{
	char	**tokens;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '#')
		{
			line[i] = '\0';
			break ;
		}
		i++;
	}
	tokens = ft_split(line, ' ');
	return (tokens);
}

bool	process_line(char *line, t_scene *scene)
{
	char	**tokens;
	bool	success;

	tokens = tokenize_line(line);
	if (!tokens)
		return (printf("Error: Memory allocation failed\n"), false);
	if (!tokens[0] || tokens[0][0] == '\n')
		return (ft_free_split(tokens), true);
	if (ft_strncmp(tokens[0], "A", 2) == 0)
		success = parse_ambient(tokens, scene);
	else if (ft_strncmp(tokens[0], "C", 2) == 0)
		success = parse_camera(tokens, scene);
	else if (ft_strncmp(tokens[0], "L", 2) == 0)
		success = parse_light(tokens, scene);
	else if (ft_strncmp(tokens[0], "sp", 3) == 0)
		success = parse_sphere(tokens, scene);
	else if (ft_strncmp(tokens[0], "pl", 3) == 0)
		success = parse_plane(tokens, scene);
	else if (ft_strncmp(tokens[0], "cy", 3) == 0)
		success = parse_cylinder(tokens, scene);
	else
		success = (printf("Error: Unknown identifier '%s'\n", tokens[0]), 0);
	ft_free_split(tokens);
	return (success);
}
