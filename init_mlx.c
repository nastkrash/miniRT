/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakrash <anakrash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:15 by anakrash          #+#    #+#             */
/*   Updated: 2025/04/21 18:28:16 by anakrash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}

void	setup_hooks(t_data *data)
{
	mlx_key_hook(data->mlx, &key_handler, data);
	mlx_loop_hook(data->mlx, &render_frame, data);
}

bool	init_mlx(t_data *data)
{
	data->mlx = mlx_init(WID, WIN_HEIGHT, "MiniRT", true);
	if (!data->mlx)
		return (printf("Error: Failed to initialize MLX42\n"), false);
	data->img = mlx_new_image(data->mlx, WID, WIN_HEIGHT);
	if (!data->img)
		return (printf("Error: Failed to create image\n"), false);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
		return (printf("Error: Failed to add image to window\n"), false);
	setup_hooks(data);
	return (true);
}
