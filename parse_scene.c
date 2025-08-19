/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:37 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/21 18:32:10 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_scene(t_scene *scene)
{
	ft_lstclear(&scene->spheres, free);
	ft_lstclear(&scene->planes, free);
	ft_lstclear(&scene->cylinders, free);
}

static bool	validate_scene_requirements(t_scene *scene)
{
	if (!scene->ambient.is_set || !scene->camera.is_set || !scene->light.is_set)
	{
		printf("Error: Missing required elements (A, C, or L)\n");
		free_scene(scene);
		return (false);
	}
	return (true);
}

// it will delete next line.
static char	*get_next_line_wrapper(int fd)
{
	char	*line;
	int		len;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	if (line[len] == '\n')
		line[len] = '\0';
	return (line);
}

bool	parse_scene(char *file, t_data *data)
{
	int		fd;
	char	*line;
	bool	success;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), false);
	success = true;
	line = get_next_line_wrapper(fd);
	while (success && line)
	{
		success = process_line(line, &data->scene);
		free(line);
		if (success)
			line = get_next_line_wrapper(fd);
	}
	close(fd);
	if (!success)
	{
		free_scene(&data->scene);
		return (false);
	}
	return (validate_scene_requirements(&data->scene));
}
